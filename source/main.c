#include <windows.h> // only runs on Windows

#include "aes.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define EXAMPLE_AES_KEY_LEN_IN_BITS		256
#define EXAMPLE_AESKEY_LEN_IN_BYTES		(EXAMPLE_AES_KEY_LEN_IN_BITS / 8)
extern int Boot_Log(char* format, ...);

int main(void) {

	Sleep(100);

	Boot_Log("Hello World!");
	

	FILE* f = fopen("c:\\input.txt", "rb");
	fseek(f, 0, SEEK_END);
	long fsize = ftell(f);
	fseek(f, 0, SEEK_SET);  /* same as rewind(f); */

	char* string = malloc(fsize + 1);
	fread(string, 1, fsize, f);
	fclose(f);

	string[fsize] = 0;
	

	mbedtls_aes_context aes;
	unsigned char key[EXAMPLE_AESKEY_LEN_IN_BYTES];
	/* TODO create an AES Key ; Just set random values here */
	
	unsigned char iv[16] ="aa";
	//Boot_Log("The iv Text  : %s", iv);
	unsigned char iv2[16] = "aa";

	unsigned char* output = malloc(((fsize + 15) / 16) * 16);
	unsigned char* decrypt_message = malloc(((fsize + 15) / 16) * 16);
	

	mbedtls_aes_setkey_enc(&aes, key, EXAMPLE_AES_KEY_LEN_IN_BITS);

	mbedtls_aes_crypt_cbc(&aes, MBEDTLS_AES_ENCRYPT, 16, iv, string, output);
	//output[16] = '\0'; /* Let us terminate the cipher text */

	Boot_Log("The Plain Text   : %s", string);
	//Boot_Log("The Cipher Text  : %s", output);
	//Boot_Log("The iv Text  : %s", iv);
	//Boot_Log("The key Text  : %s", key);

	mbedtls_aes_setkey_dec(&aes, key, EXAMPLE_AES_KEY_LEN_IN_BITS);

	mbedtls_aes_crypt_cbc(&aes, MBEDTLS_AES_DECRYPT, 16, iv2, output, decrypt_message);


	Boot_Log("The Decrypted Text  : %s", decrypt_message);
	
	/*while (0) {
		Sleep(1000);
		Boot_Log("I am alive!");
	}*/
	
	return 0;
}
