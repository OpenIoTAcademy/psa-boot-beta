#include "boot_security.h"
#include "simulation.h"

/* Remove the include */
#include <windows.h> // only runs on Windows

#include "mbedtls\aes.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hal_log.h"

#define EXAMPLE_AES_KEY_LEN_IN_BITS		256
#define EXAMPLE_AESKEY_LEN_IN_BYTES		(EXAMPLE_AES_KEY_LEN_IN_BITS / 8)
#define AES_IV_LENGTH					(16)
#define LOG_PRINTF hal_log_printf
mbedtls_aes_context aes;
unsigned char key[EXAMPLE_AESKEY_LEN_IN_BYTES];

mbedtls_aes_context aes;

bool boot_authenticate_upgrade_package(boot_upgrade_package_t* package)
{
    return true;
}
void boot_decrypt_upgrade_package(boot_upgrade_package_t* package)
{
    unsigned char iv[16] = "aa";
    hal_log_printf("The iv Text  : %s", iv);
    unsigned char input[16] = "ZAYA";
    unsigned char output[16 + 1];
    hal_log_printf("The Plain Text   : %s",input);
    mbedtls_aes_setkey_dec(&aes, key, EXAMPLE_AES_KEY_LEN_IN_BITS);
    mbedtls_aes_crypt_cbc(&aes, MBEDTLS_AES_DECRYPT, 16, iv, input, output);
    hal_log_printf("The Output Text   : %s", output);
    hal_log_printf("The Key Text   : %s", key);
}