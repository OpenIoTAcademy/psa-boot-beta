/*******************************************************************************
* @file boot_security.c
*
* @brief This file authenticates with RSA-1024 and decrypts with AES-256 the
* upgrade package. 
*
******************************************************************************
*
* Copyright (c) 2020 Open IoT Academy
*
* Unauthorised copying of this file, via any medium is strictly prohibited.
*
******************************************************************************/
 
/********************************* INCLUDES ***********************************/
#include "boot_security.h"

#include "aes.h"

#include "hal_log.h"
#include "mbedtls/rsa.h"
#include "mbedtls/md.h"
#include "mbedtls/ecp.h"
#include "mbedtls/ecdsa.h"

#include "mbedtls/sha256.h"

/******************************* MACRO DEFINITIONS ******************************/

/*
 * Symmetric Key Length for Decryption
 * We use AES-256 for encryption/decryption
 */
#define DECRYPTION_KEY_LEN_IN_BITS      256
#define DECRYPTION_KEY_LEN_IN_BYTES     (DECRYPTION_KEY_LEN_IN_BITS / 8)

/*
 * Authentication Key Len
 * We use ECC P256 for authentication.
 * The public key len is 2 key len : 2 x 32
 */
#define AUTHENTICATION_KEY_LEN_IN_BYTES (64)

/***************************** TYPE DEFINITIONS ********************************/

/**************************** FUNCTION PROTOTYPES ******************************/
    
/******************************** VARIABLES ************************************/
/*
 * Decryption Key : AES-256
 * TODO : Move into secure storage
 */
static const uint8_t Decryption_Key[DECRYPTION_KEY_LEN_IN_BYTES] = 
{
    0xA5, 0xD3, 0x07, 0xF1, 0x11, 0x23, 0x37, 0xA3, 0xA8, 0xD1, 0x03, 0xDD, 0x24, 0x93, 0x22, 0xF1,
    0x34, 0xF9, 0xC4, 0xA5, 0x75, 0x97, 0x98, 0xA7, 0x17, 0xE3, 0xA1, 0x36, 0xC3, 0xBA, 0xC3, 0x13
};

/*
 * Authentication Key : ECC P256R1
 * TODO : Move into secure storage
 */
static const uint8_t Authentication_Key[AUTHENTICATION_KEY_LEN_IN_BYTES + 1] =
{
    /* Old key format starts with 0x04 prefix */
    0x04,

    0xBB, 0x00, 0x18, 0x3A, 0xF6, 0xE9, 0xCC, 0xC4, 0x80, 0xCE, 0x48, 0xD9, 0x18, 0x93, 0x90, 0x5E,
    0xDA, 0x10, 0x36, 0x4F, 0x7E, 0x79, 0x51, 0x85, 0xA7, 0x1F, 0x1B, 0x27, 0x2A, 0x4C, 0xC2, 0xB6,
    0xF5, 0xE8, 0x5F, 0xE3, 0x1D, 0xA6, 0x39, 0x84, 0x83, 0x25, 0x5B, 0x9B, 0x1D, 0xC0, 0x3C, 0x9E,
    0x92, 0xED, 0xC0, 0xAC, 0x85, 0x90, 0xFB, 0x6B, 0x1A, 0x5E, 0x9A, 0x14, 0x63, 0x23, 0x30, 0xAF,
};

/**************************** PRIVATE FUNCTIONS *******************************/

/*
 * @brief gets ecp key pair structure from the raw public key
 * 
 * @param public_key public key to convert
 * @param key_len public key length
 * @param[out] ecp ecp object to fill
 * 
 * @return 0 if success otherwise a negative error
 * 
 */
int get_ecp_keypair(const uint8_t* public_key, size_t key_len, mbedtls_ecp_keypair* ecp)
{
    int ret;
    mbedtls_ecp_keypair_init(ecp);
    mbedtls_ecp_group_load(&ecp->grp, MBEDTLS_ECP_DP_SECP256R1);
    ret = mbedtls_ecp_point_read_binary(&ecp->grp, &ecp->Q, public_key, key_len);
    if (ret != 0) return ret;

    /* Check that the point is on the curve. */
    return mbedtls_ecp_check_pubkey(&ecp->grp, &ecp->Q);
}

/*
 * @brief Verifies a ecdsa signature
 *
 * @param ecp ecp instance to keep the public key
 * @param hash hash to verify
 * @param hash_length hash length
 * @param signature signature of the hash
 * @param signature signature length
 *
 * @return true if the verification is success otherwise false
 *
 */
static bool ecdsa_verify_signature(mbedtls_ecp_keypair* ecp, const uint8_t* hash, size_t hash_length, const uint8_t* signature, size_t signature_length)
{
    int ret;
    mbedtls_mpi r, s;
    #define PSA_BITS_TO_BYTES(bits) (((bits) + 7) / 8)
    size_t curve_bytes = PSA_BITS_TO_BYTES(ecp->grp.pbits);

    mbedtls_mpi_init(&r);
    mbedtls_mpi_init(&s);

    if (signature_length != 2 * curve_bytes) {
        return false;
    }

    MBEDTLS_MPI_CHK(mbedtls_mpi_read_binary(&r, signature, curve_bytes));
    MBEDTLS_MPI_CHK(mbedtls_mpi_read_binary(&s, signature + curve_bytes, curve_bytes));

    ret = mbedtls_ecdsa_verify(&ecp->grp, hash, hash_length, &ecp->Q, &r, &s);

cleanup:
    mbedtls_mpi_free(&r);
    mbedtls_mpi_free(&s);

    return (ret == 0);
}
/****************************  PUBLIC FUNCTIONS *******************************/

/*
 * @brief Authenticates the upgrade package
 *
 * @param package to be authenticated upgrade package
 *
 * @return true if the authentication is success otherwise false
 *
 */
bool boot_authenticate_upgrade_package(boot_upgrade_package_t* package)
{
    uint8_t hash[32];
    mbedtls_ecp_keypair ecp_keypair;

    /*
     * Compute the SHA-256 hash of the input file
     */ 
    mbedtls_sha256_ret(package->image, package->metadata.size, hash, false);

    /*
     * mbedTLS ECDSA verify needs the public key in RFC7748 format in a ECP KeyPair structure
     */
    get_ecp_keypair(Authentication_Key, sizeof(Authentication_Key), &ecp_keypair);

    /* Verify the signature of the hash */
    return ecdsa_verify_signature(&ecp_keypair, hash, sizeof(hash), package->metadata.signature, sizeof(package->metadata.signature));
}

/*
* @brief This function decrypts the upgrade package.
*
* @param package to be decrypted upgrade package which includes all details about the upgrade
* 
* @return none
*/
void boot_decrypt_upgrade_package(boot_upgrade_package_t* package)
{
    mbedtls_aes_context aes;

    /*
     * Image represents upgrade package in this function,
     * we use the image such as input
     * 
     */
    uint8_t* input = package->image;

    /*
     * We will be decrypting the same memory location
     * so let the input and the output be the same.
     */
    uint8_t* output = input;
   
    mbedtls_aes_setkey_dec(&aes, Decryption_Key, DECRYPTION_KEY_LEN_IN_BITS);

    mbedtls_aes_crypt_cbc(&aes, MBEDTLS_AES_DECRYPT, package->metadata.size, package->metadata.iv, input, output);
}
