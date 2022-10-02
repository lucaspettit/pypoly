#ifndef GEAR_RATIOS_H
#define GEAR_RATIOS_H
#include <iostream>

namespace gt {
    using std::uint8_t;
    
    class GearRatios {
        public:
            GearRatios() = default;
            GearRatios(float gears[], uint8_t size);
            ~GearRatios() = default;
            float getRatio(uint8_t gear);
            uint8_t nGears() { return _nGears; }
            uint8_t maxGears() { return _maxGears; }

            GearRatios& operator=(const GearRatios& other) {
                if(&other == this) { return *this; }
                if(_nGears != other._nGears) { _nGears = other._nGears; }
                for(uint8_t i = 0; i < _maxGears; i++) {
                    if(_gears[i] != other._gears[i]) { _gears[i] = other._gears[i]; }
                }
                return *this;
            }

        private:
            static const int8_t _maxGears = 8;
            float _gears[GearRatios::_maxGears] = {0};
            int8_t _nGears;
    };
}

#endif