import numpy as np
import math


def block_to_bytes(str_in):
    if str_in[0:2] != "0x":
        raise ValueError("Expecting a hexadecimal input, eg: 0x1a30")
    
    if len(str_in) != 34:
        raise ValueError("Expecting a 128 bit input") 
    
    words = [(str_in[i:i+8]) for i in range(2, len(str_in), 8)]     # split input into slices of 8 (from 2 to remove "0x")
    words[len(words)-1] = words[len(words)-1].ljust(8,'0') # zero pad last value 
    
    if len(words)<4:                                            # add words to fill block size
        for i in range(4-len(words)%4):
            words.append('0')   
    
    words_ints = [0]*len(words)
    words_bytes = [0]*len(words)
    for i in range(len(words)):                                   # turn hex to int (,16 for base)
        words_ints[i] = int(words[i], 16)
        words_bytes[i] = words_ints[i].to_bytes(4, byteorder='little', signed=False)
    
    bytes_out = words_bytes[0]+words_bytes[1]+words_bytes[2]+words_bytes[3]
    
    return bytes_out


def format_array(in_str):
    in_hex = hex(int(''.join(str(ord(c)) for c in in_str)))
        
    in_split = [(in_hex[i:i+8]) for i in range(2, len(in_hex), 8)]     # split input into slices of 8 (from 2 to remove "0x")
    in_split[len(in_split)-1] = in_split[len(in_split)-1].ljust(8,'0') # zero pad last value 
    if len(in_split)%4 !=0:                                            # add words to fill block size
        for i in range(4-len(in_split)%4):
            in_split.append('0')                
    input_ints = [0]*len(in_split)
    for i in range(len(input_ints)):                                   # turn hex to int (,16 for base)
        input_ints[i] = int(in_split[i], 16)
    return input_ints


