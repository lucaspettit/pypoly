#include "../../include/utils/system.h"

namespace gt {
    System::System() {
        short int word = 0x0001;
        char *b = (char *) &word;
        endian = (b[0] ? Endian::LITTLE : Endian::BIG);
    }

    Endian System::getEndian() {
        return endian;
    }

    void System::toSystemEndian(char b[], int size, Endian srcEndian) {
        if(srcEndian == endian) {
            return;
        }
        System::flipEndian(b, size);
    }

    void System::flipEndian(char b[], int size) {
        for(int i = 0; i < (int) size / 2; i++) {
            char left = b[i];
            char right = b[size - i - 1];
            b[i] = right;
            b[size - i - 1] = left;
        }
    }
}