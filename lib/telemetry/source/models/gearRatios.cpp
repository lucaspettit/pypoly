#include "../../include/models/gearRatios.h"

namespace gt {
    GearRatios::GearRatios(float gears[], uint8_t size): _nGears(size) {
        if(size > 10 || size < 0) {
            throw std::invalid_argument("Invalid argument for size");
        }
        for(uint8_t i = 0; i < size; i++) {
            _gears[i] = gears[i];
        }
    }

    float GearRatios::getRatio(uint8_t gear) {
        if(gear <= 0 || gear > _nGears) {
            throw std::invalid_argument("Invalid gear");
        }
        return _gears[gear - 1];
    }
}