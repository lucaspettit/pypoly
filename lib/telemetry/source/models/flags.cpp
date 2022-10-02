#include "../../include/models/flags.h"

namespace gt {
        Flags::Flags(uint16_t byte) {
        uint16_t mask = 1;
        _carOnTrack = byte & mask;
        _paused = byte & (++mask);
        _loadingOrProcessing = byte & (++mask);
        _inGear = byte & (++mask);
        _hasTurbo = byte & (++mask);
        _revLimiterAlertActive = byte & (++mask);
        _handBrakeActive = byte & (++mask);
        _lightsActive = byte & (++mask);
        _lightsHighBeamsActive = byte & (++mask);
        _lightsLowBeamsActive = byte & (++mask);
        _asmActive = byte & (++mask);
        _tcsActive = byte & (++mask);
        _unused1 = byte & (++mask);
        _unused2 = byte & (++mask);
        _unused3 = byte & (++mask);
        _unused4 = byte & (++mask);
    }
}