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

/***************************** TYPE DEFINITIONS ********************************/

/**************************** FUNCTION PROTOTYPES ******************************/
    
/******************************** VARIABLES ************************************/

static const uint8_t Decryption_Key[DECRYPTION_KEY_LEN_IN_BYTES];

/**************************** PRIVATE FUNCTIONS *******************************/


/****************************  PUBLIC FUNCTIONS *******************************/

bool boot_authenticate_upgrade_package(boot_upgrade_package_t* package)
{
   return true;
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
       

/*We will be decrypting the same memory location
*so let the input and the output be the same.
*/
    uint8_t* output = input;
   
    mbedtls_aes_setkey_dec(&aes, Decryption_Key, DECRYPTION_KEY_LEN_IN_BITS);

    mbedtls_aes_crypt_cbc(&aes, MBEDTLS_AES_DECRYPT, package->metadata.size, package->metadata.iv, input, output);
}