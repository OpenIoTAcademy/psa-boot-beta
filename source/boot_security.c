#include "boot_security.h"
#include "aes.h"
#include "hal_log.h"
#define EXAMPLE_AES_KEY_LEN_IN_BITS		256
#define EXAMPLE_AESKEY_LEN_IN_BYTES		(EXAMPLE_AES_KEY_LEN_IN_BITS / 8)
#define AES_IV_LENGTH					(16)

bool boot_authenticate_upgrade_package(boot_upgrade_package_t* package)
{
    return true;
}
void boot_decrypt_upgrade_package(boot_upgrade_package_t* package)
{
    mbedtls_aes_context aes;
    unsigned char key[EXAMPLE_AESKEY_LEN_IN_BYTES];
    uint8_t* input = package->image;
    uint8_t* output = input;
   
    mbedtls_aes_setkey_dec(&aes, key, EXAMPLE_AES_KEY_LEN_IN_BITS);
    mbedtls_aes_crypt_cbc(&aes, MBEDTLS_AES_DECRYPT, package->metadata.size, package->metadata.iv, input, output);
}