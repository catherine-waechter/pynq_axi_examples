#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <ap_int.h>

#define ECB 1
#include "aes.h"

void aes(ap_uint<128> key, uint8_t *input, uint8_t *output);

int main(void)
{
	uint8_t in[] = { 0xe2, 0xbe, 0xc1, 0x6b, 0x96, 0x9f, 0x40, 0x2e, 0x11, 0x7e, 0x3d, 0xe9, 0x2a, 0x17, 0x93, 0x73 };
	uint8_t out[] = { 0xb4, 0x7b, 0xd7, 0x3a, 0x60, 0x36, 0x7a, 0x0d, 0xf3, 0xca, 0x9e, 0xa8, 0x97, 0xef, 0x66, 0x24 }; // expected output
	ap_uint<128> key = "0x09cf4f3cabf7158828aed2a62b7e1516";
	uint8_t output[16];

	aes(key, in, output);

	printf("Encrypting ...");

	if (0 == memcmp((char*) out, (char*) output, 16)) {
        	printf("SUCCESS!\n");
		return(0);
	} 
	else {
        	printf("FAILURE!\n");
        	printf("Result:");
		for(int i=0; i<16; i++){
			printf("%x", output[i]);
		}
		printf("\n");
		return(1);
    	}
}
