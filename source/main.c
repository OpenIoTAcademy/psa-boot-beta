
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
	int rounded_file_size = (((file_size + 15) / 16) * 16);
	unsigned char* input = malloc(rounded_file_size);
	if (f_pointer == NULL) {
		printf("Could not open file %s", filename);
		/*return 1;*/
	}
	
	fread(input, 1, file_size, f_pointer);
	fclose(f_pointer);
	input[file_size] = 0;
	
	unsigned char* enc_output = (char*)malloc(rounded_file_size);
	unsigned char* dec_output = (char*)malloc(rounded_file_size);


	mbedtls_aes_setkey_enc(&aes, key, EXAMPLE_AES_KEY_LEN_IN_BITS);
	/*enc_output[16] = '\0'; /* Let us terminate the cipher text */
	mbedtls_aes_crypt_cbc(&aes, MBEDTLS_AES_ENCRYPT, rounded_file_size, iv, input, enc_output);
	
	Boot_Log("The Plain Text   : %s", input);
	Boot_Log("The Cipher Text  : %s", enc_output);

	mbedtls_aes_setkey_dec(&aes, key, EXAMPLE_AES_KEY_LEN_IN_BITS);
	mbedtls_aes_crypt_cbc(&aes, MBEDTLS_AES_DECRYPT, rounded_file_size, iv2, enc_output, dec_output);
	

	Boot_Log("The decrypted text: %s", dec_output);
	
	free(input);
	free(enc_output);
	free(dec_output);
	
	int cnt = 0;
	while (1) {
		Sleep(1000);
		Boot_Log("I am alive!");
	}
	
	
	
	return 0;
}