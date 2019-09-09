#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <ap_int.h>

#include "aes.h"

typedef struct{
	uint8_t data[16];
	ap_uint<1> user;		// USER signal
	ap_uint<1> last; 	// TLAST signal
} stream_type;

void aes(ap_uint<128> key, stream_type* in_stream, stream_type* out_stream);

int main(void)
{
	ap_uint<128> key = "0x09cf4f3cabf7158828aed2a62b7e1516";
	stream_type output_stream, input_stream;	

	uint8_t in[] = { 0xe2, 0xbe, 0xc1, 0x6b, 0x96, 0x9f, 0x40, 0x2e, 0x11, 0x7e, 0x3d, 0xe9, 0x2a, 0x17, 0x93, 0x73};
	uint8_t out[] = { 0xb4, 0x7b, 0xd7, 0x3a, 0x60, 0x36, 0x7a, 0x0d, 0xf3, 0xca, 0x9e, 0xa8, 0x97, 0xef, 0x66, 0x24};

    	input_stream.user = 1;			// initialise the input stream
       	input_stream.last = 1;
       	for(int i = 0; i<16; i++){		
		input_stream.data[i]= in[i];
	}

   	aes(key, &input_stream, &output_stream);

       if (0 == memcmp((char*) out, (char*) output_stream.data, 16)) {
           printf("SUCCESS!\n");
       } else {
           printf("FAILURE!\n");
           int i;
           printf("Result:");
           for(i=0; i<16; i++){
           	printf("%x", output_stream.data[i]);
           }
           printf("\n");
           return(1);
       }

       return 0;
}
