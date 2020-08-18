#include "boot_security.h"
#include "aes.h"
#include "hal_log.h"
#include <boot.c>
//#define AES_IV_LENGTH					(16)
/*
* Symmetric Key Length for Decryption
* We use AES-256 for encryption/decryption
*/
#define DECRYPTION_KEY_LEN_IN_BITS 256
#define DECRYPTION_KEY_LEN_IN_BYTES (DECRYPTION_KEY_LEN_IN_BITS / 8)

static const uint8_t Decryption_Key[DECRYPTION_KEY_LEN_IN_BYTES];

bool boot_authenticate_upgrade_package(boot_upgrade_package_t* package)
{
    return true;
}
/**
* @brief boot_decrypt_upgrade_package() function does something
* @param package Argument 1
*/
void boot_decrypt_upgrade_package(boot_upgrade_package_t* package)
{
    mbedtls_aes_context aes;
    /*
    * We will be decrypting the same memory location 
    * so let the input and the output be the same.
    */
    uint8_t* input = package->image;
    uint8_t* output = input;
   
    mbedtls_aes_setkey_dec(&aes, Decryption_Key, EXAMPLE_AES_KEY_LEN_IN_BITS);
    mbedtls_aes_crypt_cbc(&aes, MBEDTLS_AES_DECRYPT, package->metadata.size, package->metadata.iv, input, output);
}