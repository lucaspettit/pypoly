#ifndef SALSA20_H
#define SALSA20_H

#include <cassert>
#include <climits>
#include <cstdint>
#include <cstring>

namespace gt {

    using std::size_t;
    using std::int32_t;
    using std::uint8_t;
    using std::uint32_t;

    /**
     * Define Salsa20 object. Supports 256-bit keys
     */
    class Salsa20 {
        public:
            enum: size_t {
                VECTOR_SIZE = 16,
                BLOCK_SIZE = 64,
                KEY_SIZE = 32,
                IV_SIZE = 8
            };

            Salsa20(const uint8_t *key = nullptr);
            Salsa20(const Salsa20&) = default;
            Salsa20(Salsa20&&) = default;
            ~Salsa20() = default;
            Salsa20& operator = (const Salsa20&) = default;
            Salsa20& operator = (Salsa20&) = default;

            // Setters 
            void setKey(const uint8_t *key);
            void setIv(const uint8_t *iv);
            
            // functions
            void generateKeyStream(uint8_t output[BLOCK_SIZE]);
            void processBlocks(const uint8_t *input, uint8_t *output, size_t numBlocks);
            void processBytes(const uint8_t *input, uint8_t *output, size_t numBytes);
        
        private:
            uint32_t rotate(uint32_t value, uint32_t numBits);
            void convert(uint32_t value, uint8_t *array);
            uint32_t convert(const uint8_t *array);

            uint32_t vector_[VECTOR_SIZE];
    };
}

#endif