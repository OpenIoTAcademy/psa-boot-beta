
#include "simulation.h"

/* Remove the include */
#include <windows.h> // only runs on Windows
#include <stdio.h>
#include <string.h>
#include "aes.h"

#define EXAMPLE_AES_KEY_LEN_IN_BITS		256
#define EXAMPLE_AESKEY_LEN_IN_BYTES		(EXAMPLE_AES_KEY_LEN_IN_BITS / 8)
#define AES_IV_LENGTH					(16)

extern int Boot_Log(char* format, ...);

int main(void) {

	Sleep(100);

	Boot_Log("Hello World!");

	mbedtls_aes_context aes;

	unsigned char key[EXAMPLE_AESKEY_LEN_IN_BYTES];
	/* TODO create an AES Key ; Just set random values here */


	/*unsigned char iv[AES_IV_LENGTH];*/
	/* TODO create an IV ; Just set random values here */
	unsigned char iv[16] = "a";
	unsigned char iv2[16] = "a";
	FILE* f_pointer;
	char* filename = "c://Exp_Bin_File.txt";
	f_pointer = fopen(filename, "r");
	fseek(f_pointer, 0, SEEK_END);
	long file_size = ftell(f_pointer);
	rewind(f_pointer);
	unsigned char* input = (char*)malloc(file_size * sizeof(char));

	if (f_pointer == NULL) {
		printf("Could not open file %s", filename);
		/*return 1;*/
	}
	while (fgets(input, file_size + 1, f_pointer) != NULL) {
		Boot_Log("important : %s", input);


	}
	fclose(f_pointer);
	unsigned char* enc_output = (char*)malloc((file_size + 2) * sizeof(char));
	unsigned char* dec_output = (char*)malloc((file_size + 2) * sizeof(char));


	mbedtls_aes_setkey_enc(&aes, key, EXAMPLE_AES_KEY_LEN_IN_BITS);


	/*enc_output[16] = '\0'; /* Let us terminate the cipher text */
	/*If-else structures are added for flexibilty. EXP: "Example Binary File" text contains 19 characters, AES with 16 is powerless for this.
	AES with 32 can encrypt and decrypt successfully.Additionally, "Internship" text contains 10 char. , AES with 16 can handle succesfully.*/

	if (file_size <= 16)
	{
		mbedtls_aes_crypt_cbc(&aes, MBEDTLS_AES_ENCRYPT, 16, iv, input, enc_output);
	}
	else if ((file_size > 16) && (file_size <= 32))
	{
		mbedtls_aes_crypt_cbc(&aes, MBEDTLS_AES_ENCRYPT, 32, iv, input, enc_output);
	}
	else if ((file_size > 32) && (file_size <= 64))
	{
		mbedtls_aes_crypt_cbc(&aes, MBEDTLS_AES_ENCRYPT, 64, iv, input, enc_output);
	}
	Boot_Log("The Plain Text   : %s", input);
	Boot_Log("The Cipher Text  : %s", enc_output);

	mbedtls_aes_setkey_dec(&aes, key, EXAMPLE_AES_KEY_LEN_IN_BITS);

	if (file_size <= 16)
	{
		mbedtls_aes_crypt_cbc(&aes, MBEDTLS_AES_DECRYPT, 16, iv2, enc_output, dec_output);
	}
	else if ((file_size > 16) && (file_size <= 32))
	{
		mbedtls_aes_crypt_cbc(&aes, MBEDTLS_AES_DECRYPT, 32, iv2, enc_output, dec_output);
	}
	else if ((file_size > 32) && (file_size <= 64))
	{
		mbedtls_aes_crypt_cbc(&aes, MBEDTLS_AES_DECRYPT, 64, iv2, enc_output, dec_output);
	}

	Boot_Log("The decrypted text: %s", dec_output);
	int cnt = 0;
	while (1) {
		Sleep(1000);
		Boot_Log("I am alive!");
	}

	return 0;
}