#ifndef CIPHER_H
#define CIPHER_H

#include <string>
#include "salsa20.h"

namespace gt {
    using std::size_t;
    using std::int32_t;
    using std::uint8_t;
    using std::uint32_t;

    class Cipher {
        public:
            Cipher() = default;
            ~Cipher() = default;
            
            /**
             * Populates the output packet with the input packet's decrypted content.
             * Returns 0 on successful decryption
             */
            int decrypt(const char* input, char* output, int size);
        
        private:
            const std::string keyStr = "Simulator Interface Packet GT7 ver 0.0"; 
            const uint8_t *key = reinterpret_cast<const uint8_t*>(&keyStr[0]);
            const uint32_t ivMask = 0xDEADBEAF;
            const uint32_t validationKey = 0x47375330;
            Salsa20 salsa = Salsa20(key);

            // functions
            void setIv(const char* input);
    };
}

#endif