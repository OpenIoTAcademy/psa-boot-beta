#include "./simulator/simulation.h"

/* Remove the include */
#include <windows.h> // only runs on Windows

#include "C:\Users\ozdem\OneDrive\Desktop\psa-boot-beta\external\mbed-crypto\include\mbedtls/aes.h"
#include "C:\Users\ozdem\OneDrive\Desktop\psa-boot-beta\external\mbed-crypto\include\mbedtls/config.h"
#include <aes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define EXAMPLE_AES_KEY_LEN_IN_BITS		256
#define EXAMPLE_AESKEY_LEN_IN_BYTES		(EXAMPLE_AES_KEY_LEN_IN_BITS / 8)
#define AES_IV_LENGTH					(16)
extern int Boot_Log(char* format, ...);

int main(void) {
	Sleep(100);

	Boot_Log("Hello World!");



	mbedtls_aes_context aes ;
//	FILE* fp = fopen("file1.txt", "w+");
//	fputs("ZAYAIntership Training1,", fp);
	FILE* fpt = fopen("file.txt", "rb");
	fseek(fpt, 0, SEEK_END);
	long fsize = ftell(fpt);
	fseek(fpt, 0, SEEK_SET);  /* same as rewind(f); */

	char* string = malloc(fsize + 1);
	fread(string, 1, fsize, fpt);

	fclose(fpt);
	//fclose(fp);
	/* File pointer to hold reference to our file */

	string[fsize] = 0;

	unsigned char key[EXAMPLE_AESKEY_LEN_IN_BYTES];
	/* TODO create an AES Key ; Just set random values here */

	unsigned char iv[16] = "aa";

	unsigned char iv2[16] = "aa";
	/* TODO create an IV ; Just set random values here */


	unsigned char* output[] = malloc(((fsize + 15) / 16) * 16);
	unsigned char* decrypt_output = malloc(((fsize + 15) / 16) * 16);
	
	
	unsigned char input[16] = "ZAYA Internship";
	unsigned char output[16 +1 ];
	mbedtls_aes_setkey_enc(&aes, key, EXAMPLE_AES_KEY_LEN_IN_BITS);


	mbedtls_aes_crypt_cbc(&aes, MBEDTLS_AES_ENCRYPT, 16, iv, string, output);

	
	Boot_Log("The Plain Text   : %s", string);
	//Boot_Log("The Cipher Text  : %s", output);
//	Boot_Log("The iv Text  : %s", iv);
//	Boot_Log("The key Text  : %s", key);
	
	mbedtls_aes_setkey_enc(&aes, key, EXAMPLE_AES_KEY_LEN_IN_BITS);
	mbedtls_aes_setkey_dec(&aes, key, EXAMPLE_AES_KEY_LEN_IN_BITS);

	mbedtls_aes_crypt_cbc(&aes, MBEDTLS_AES_ENCRYPT, 16, iv, input, output);

	output[16] = '\0';

	mbedtls_aes_crypt_cbc(&aes, MBEDTLS_AES_DECRYPT, 16, iv2, output, decrypt_output);


	Boot_Log("The Plain Text   : %s", input);
	Boot_Log("The Cipher Text  : %s", output);

	int cnt = 0;
	while (1) {
		Boot_Log("The Decrypted Text  : %s", decrypt_output);

		int cnt = 0;
		/*while (1) {
			Sleep(1000);
			Boot_Log("I am alive!");
		}*/

		return 0;

	}
}
