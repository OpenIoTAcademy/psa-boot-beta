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
 * Authentication Key : ECC P256
 * TODO : Move into secure storage
 */
static const uint8_t Authentication_Key[AUTHENTICATION_KEY_LEN_IN_BYTES] =
{
    0xBB, 0x00, 0x18, 0x3A, 0xF6, 0xE9, 0xCC, 0xC4, 0x80, 0xCE, 0x48, 0xD9, 0x18, 0x93, 0x90, 0x5E,
    0xDA, 0x10, 0x36, 0x4F, 0x7E, 0x79, 0x51, 0x85, 0xA7, 0x1F, 0x1B, 0x27, 0x2A, 0x4C, 0xC2, 0xB6,
    0xF5, 0xE8, 0x5F, 0xE3, 0x1D, 0xA6, 0x39, 0x84, 0x83, 0x25, 0x5B, 0x9B, 0x1D, 0xC0, 0x3C, 0x9E,
    0x92, 0xED, 0xC0, 0xAC, 0x85, 0x90, 0xFB, 0x6B, 0x1A, 0x5E, 0x9A, 0x14, 0x63, 0x23, 0x30, 0xAF,
};

/**************************** PRIVATE FUNCTIONS *******************************/

/****************************  PUBLIC FUNCTIONS *******************************/

bool boot_authenticate_upgrade_package(boot_upgrade_package_t* package)
{

    //mbedtls_ecp_context aes;
    unsigned char hash[32];
    int ret = 1;
    int ret2,ret3;
  
   
    /*
    * Compute the SHA-256 hash of the input file and
    * verify the signature
    */
    uint8_t* imagePtr = package->image;
    uint8_t* signaturePtr = package->metadata.signature;
 
    ret = mbedtls_sha256_ret(package->image, package->metadata.size, hash, 0);
    mbedtls_ecdsa_context ctx_verify;
  
    mbedtls_ecdsa_init(&ctx_verify);
    ret3 = mbedtls_ecdsa_from_keypair(&ctx_verify, Authentication_Key);
    //mbedtls_ecp_copy(&ctx_verify.Q, Authentication_Key);
    
    ret2 = mbedtls_ecdsa_read_signature(&ctx_verify, hash, sizeof(hash), package->metadata.signature, 64);
    LOG_PRINTF("Authentication : %d", ret2);
  
    return ret2;
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

    {
        output[29] = 0;
        LOG_PRINTF("");
        LOG_PRINTF("Encrypted message : %s", output);
        LOG_PRINTF("");
    }
}
