#ifndef FLAGS_H
#define FLAGS_H
#include <iostream>

namespace gt {
    using std::uint16_t;

    class Flags {
        public:
            Flags() = default;
            Flags(uint16_t byte);
            
            bool carOnTrack() { return _carOnTrack; }
            bool paused() { return _paused; }
            bool laodingOrProcessing() { return _loadingOrProcessing; }
            bool inGear() { return _inGear; }
            bool hasTurbo() { return _hasTurbo; }
            bool revLimiterAlertActive() { return _revLimiterAlertActive; }
            bool handBreakActive() { return _handBrakeActive; }
            bool lightsActive() { return _lightsActive; }
            bool lightsHighBeamsActive() { return _lightsHighBeamsActive; }
            bool lightsLowBeamsActive() { return _lightsLowBeamsActive; }
            bool asmActive() { return _asmActive; }
            bool tcsActive() { return _tcsActive; }
            bool unused1() { return _unused1; }
            bool unused2() { return _unused2; }
            bool unused3() { return _unused3; }
            bool unused4() { return _unused4; }

            Flags& operator=(const Flags& other) {
                if(&other == this) { return *this; }
                if(_carOnTrack != other._carOnTrack) { _carOnTrack = other._carOnTrack; }
                if(_paused != other._paused) { _paused = other._paused; }
                if(_loadingOrProcessing != other._loadingOrProcessing) { _loadingOrProcessing = other._loadingOrProcessing; }
                if(_inGear != other._inGear) { _inGear = other._inGear; }
                if(_hasTurbo != other._hasTurbo) { _hasTurbo = other._hasTurbo; }
                if(_revLimiterAlertActive != other._revLimiterAlertActive) { _revLimiterAlertActive = other._revLimiterAlertActive; }
                if(_handBrakeActive != other._handBrakeActive) { _handBrakeActive = other._handBrakeActive; }
                if(_lightsActive != other._lightsActive) { _lightsActive = other._lightsActive; }
                if(_lightsHighBeamsActive != other._lightsHighBeamsActive) { _lightsHighBeamsActive = other._lightsHighBeamsActive; }
                if(_lightsLowBeamsActive != other._lightsLowBeamsActive) { _lightsLowBeamsActive = other._lightsLowBeamsActive; }
                if(_asmActive != other._asmActive) { _asmActive = other._asmActive; }
                if(_tcsActive != other._tcsActive) { _tcsActive = other._tcsActive; }
                if(_unused1 != other._unused1) { _unused1 = other._unused1; }
                if(_unused2 != other._unused2) { _unused2 = other._unused2; }
                if(_unused3 != other._unused3) { _unused3 = other._unused3; }
                if(_unused4 != other._unused4) { _unused4 = other._unused4; }
                return *this;
            }

        private:
            bool _carOnTrack; // 1
            bool _paused; // 2
            bool _loadingOrProcessing; // 4
            bool _inGear; // 8
            bool _hasTurbo; // 16
            bool _revLimiterAlertActive; // 32
            bool _handBrakeActive; // 64
            bool _lightsActive; // 128
            bool _lightsHighBeamsActive; // 256
            bool _lightsLowBeamsActive; // 512
            bool _asmActive; // 1024
            bool _tcsActive; // 2048
            bool _unused1;
            bool _unused2;
            bool _unused3;
            bool _unused4;
    };
}

#endif