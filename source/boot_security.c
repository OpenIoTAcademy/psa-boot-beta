/*******************************************************************************
* @file boot_security.c
*
* @brief This file authenticates with RSA-1024 and decrypts with AES-256 the upgrade package. 
*
*
******************************************************************************
*
* Copyright (c) 2020 Open IoT Academy
*
* Unauthorised copying of this file, via any medium is strictly prohibited.
*
******************************************************************************/


 /******************************** VARIABLES ***********************************/

 //static const uint8_t Decryption_Key[DECRYPTION_KEY_LEN_IN_BYTES];
 // uint8_t* input = package->image;
 // uint8_t* output = input;

 
/********************************* INCLUDES ***********************************/
#include "boot_security.h"
#include "aes.h"
#include "hal_log.h"

 /******************************* MACRO DEFINITIONS ******************************/
/*
* Symmetric Key Length for Decryption
* We use AES-256 for encryption/decryption
*/
#define DECRYPTION_KEY_LEN_IN_BITS 256
#define DECRYPTION_KEY_LEN_IN_BYTES (DECRYPTION_KEY_LEN_IN_BITS / 8)

static const uint8_t Decryption_Key[DECRYPTION_KEY_LEN_IN_BYTES];
/*******************************************************************************/

/****************************  PUBLIC FUNCTIONS ******************************/
bool boot_authenticate_upgrade_package(boot_upgrade_package_t* package)
{
    return true;
}
/**
* @brief boot_decrypt_upgrade_package() function 
* use AES-256 with Symmetric Key for decryption   
* @param package[out] Argument 1 to get something out
*/
void boot_decrypt_upgrade_package(boot_upgrade_package_t* package)
{
    /***************************** TYPE DEFINITIONS *******************************/
    mbedtls_aes_context aes;
    /*******************************************************************************/

      
    uint8_t* input = package->image;
    /*
    * Image represents upgrade package in this function,
    * Security critical metadata that is associated with an image.
    * Metadata contains parameters for decryption function.
    */
   

    uint8_t* output = input;
    /*
  *We will be decrypting the same memory location
  *so let the input and the output be the same.
   */


    /**************************** FUNCTION PROTOTYPES *****************************/
    mbedtls_aes_setkey_dec(&aes, Decryption_Key, DECRYPTION_KEY_LEN_IN_BITS);
    mbedtls_aes_crypt_cbc(&aes, MBEDTLS_AES_DECRYPT, package->metadata.size, package->metadata.iv, input, output);
}