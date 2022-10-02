#include "../../include/cipher/cipher.h"
#include <iostream>

namespace gt {
    int Cipher::decrypt(const char* input, char* output, int size) {
        this->setIv(input);
        salsa.processBytes(
            (uint8_t*) input, 
            (uint8_t*) output,
            size);
        uint32_t magic = *(uint32_t*) output;

        if (magic != validationKey) {
            output = {0}; // 0 out the bytes so they wont accidentally be used by something else;
            return -1;
        }
        return 0;
    }

    /*
     * This function extracts the IV value from the input. 
     * The IV value is a 64-bit code used by Salsa20. 
     * The upper 32-bits are directly read from the stream at position 0x40. 
     * The lower 32-bits are the upper 32 XOR'ed by 0xDEADBEAF.
     * 
     * Because the input is in little endian, the lower 32-bit's will be the
     * first 32-bits in the input.
     */
    void Cipher::setIv(const char* input) {
        uint64_t upper = *(uint32_t*) &input[0x40];
        uint64_t iv = (upper << 32) + ((uint32_t)upper ^ ivMask);
        salsa.setIv((uint8_t*) &iv);
    }
}