
#include "./simulator/simulation.h"

/* Remove the include */
#include <windows.h> // only runs on Windows

#include "C:\Users\ozdem\OneDrive\Desktop\psa-boot-beta\external\mbed-crypto\include\mbedtls/aes.h"
#include "C:\Users\ozdem\OneDrive\Desktop\psa-boot-beta\external\mbed-crypto\include\mbedtls/config.h"
#include <stdio.h>



#define EXAMPLE_AES_KEY_LEN_IN_BITS		256
#define EXAMPLE_AESKEY_LEN_IN_BYTES		(EXAMPLE_AES_KEY_LEN_IN_BITS / 8)
#define AES_IV_LENGTH					(16)

extern int Boot_Log(char* format, ...);

int main(void) {

	Sleep(100);
	FILE* fp;
	fp = fopen("file1.txt", "a+");
	fputs("ZAYAIntership Training1,", fp);
	fclose(fp);
	/*fprintf(fp, "Learning C with ZAYA\n");
	fclose(fp);*/
	Boot_Log("Hello World!");

	mbedtls_aes_context aes;

	unsigned char key[EXAMPLE_AESKEY_LEN_IN_BYTES];
	/* TODO create an AES Key ; Just set random values here */


	unsigned char iv[AES_IV_LENGTH];
	/* TODO create an IV ; Just set random values here */

	unsigned char input[16] = "ZAYA Internship";
	unsigned char output[16 + 1];

	mbedtls_aes_setkey_enc(&aes, key, EXAMPLE_AES_KEY_LEN_IN_BITS);

	mbedtls_aes_crypt_cbc(&aes, MBEDTLS_AES_ENCRYPT, 16, iv, input, output);
	output[16] = '\0'; /* Let us terminate the cipher text */

	Boot_Log("The Plain Text   : %s", input);
	Boot_Log("The Cipher Text  : %s", output);

	int cnt = 0;
	while (1) {
		Sleep(1000);
		Boot_Log("I am alive!");
	}

	return 0;

}
