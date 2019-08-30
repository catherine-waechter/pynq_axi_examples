#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <ap_int.h>

#include "aes.h"

#include <iostream>
using namespace std;

#define NBR_BLOCKS 4
static int test_encrypt_ecb(void);

void aes(ap_uint<128> key, ap_uint<128> input[NBR_BLOCKS], ap_uint<128> output[NBR_BLOCKS], int size);

typedef uint8_t state_t[4][4];


int main(void)
{
    int exit;
    printf("\nTesting AES128\n\n");

    exit = test_encrypt_ecb();
    return exit;
}


static int test_encrypt_ecb(void)
{
    ap_uint<128> key = "0x09cf4f3cabf7158828aed2a62b7e1516";
    ap_uint<128> in[NBR_BLOCKS] = {"0x7393172ae93d7e112e409f966bc1bee2", "0x45af8e519eb76fac1e03ac9cae2d8a57", "0x1a0a52efe5fbc119a35ce41130c81c46", "0xe66c3710ad2b417bdf4f9b17f69f2445"};
	ap_uint<128> out[NBR_BLOCKS] = {"0x2466ef97a89ecaf30d7a36603ad77bb4", "0x96fdbaafe785895a03b9699df5d3d585", "0xed030688881b00e3598ece2343b1cd7f", "0x04725dd48223207127e8ad3f7b0c785e" };
	ap_uint<128> output[NBR_BLOCKS];

	aes(key, in, output, sizeof(in));	// size in bytes

    printf("ECB encrypt: ");
    int i;
    if (0 == memcmp( &out,  &output, 16)) {
        printf("SUCCESS!\n");
    } else {
        printf("FAILURE!\n");
        printf("Result:");
        for(i=0; i<sizeof(in)/16; i++){
        	cout<< hex<<output[i]<<'\n';
        }
        printf("\n");
	return 1;
    }
    printf("Result:");
		for(i=0; i<sizeof(in)/16; i++){
			cout<< hex<<output[i]<<'\n';
		}
		printf("\n");
    return 0;
}
