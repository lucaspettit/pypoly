#ifndef SYSTEM_H
#define SYSTEM_H

#include <ostream>

namespace gt {
    
    enum Endian { LITTLE, BIG };

    class System {
        public:
            System();
            inline ~System() = default;

            // getters
            Endian getEndian();

            // functions
            void toSystemEndian(char b[], int size, Endian srcEndian);
            void flipEndian(char b[], int size);
        private:
            Endian endian;
    };
}

#endif