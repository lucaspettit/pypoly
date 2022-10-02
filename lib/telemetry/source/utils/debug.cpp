#include "../../include/utils/debug.h"

using namespace gt;

std::string Debug::toBiteStr(char* b, int size) {
    std::string str = "";
    for(int i = 0; i < size; i++) {
        str.append(std::bitset<8>(*b++).to_string());
        if(i < size - 1) {
            str.append(" ");
        }
    }
    return str;
}