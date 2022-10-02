#ifndef PACKET_H
#define PACKET_H

#include "vector.h"
#include "wheels.h"
#include "bounds.h"
#include "flags.h"
#include "gearRatios.h"
#include <iostream>

namespace gt { // models
    using std::uint8_t;
    using std::uint32_t;
    using std::uint64_t;

    class Packet {
        public:
            Packet(const char* buffer, int size);
            ~Packet() = default;

            uint32_t packetId() { return _packetId; }
            uint32_t carId() { return _carId; }
            uint64_t receivedTimestamp() { return _receivedTimestamp; }

            Vector position() { return _position; }
            Vector velocity() { return _velocity; }
            Vector rotation() { return _rotation; }
            Vector angularVelocity() { return _angularVelocity; }
            Vector roadPlane() { return _roadPlane; }

            Wheels wheelsSurfaceTemp() { return _wheelsSurfaceTemp; }
            Wheels wheelsRPM() { return _wheelsRevs; }
            Wheels wheelsRadious() { return _wheelsRadious; }
            Wheels suspentionHeight() { return _suspentionHeight; }

            Bounds rpmAlert() { return _alertRPM; }
            GearRatios gearRatios() { return _gearRatios; }
            Flags flags() { return _flags; }

            // Orientation to north
            float orientation() { return _orientationToNorth; }
            float bodyHeight() { return _bodyHeight; }
            float engineRPM() { return _engineRPM; }
            float gasLevel() { return _gasLevel; }
            float gasCapacity() { return _gasCapacity; }
            float carSpeed() { return _carSpeed; }
            float turboBoost() { return _turboBoost; }
            float oilPressure() {return _oilPressure; }
            float waterTemperature() { return _waterTemp; }
            float oilTemperature() { return _oilTemp; }
            float roadPlaneDistance() { return _roadPlaneDistance; }
            short lapCount() { return _lapCount; }
            short nLapsInRace() { return _lapsInRace; }
            short nCarsInRace() { return _nCarsInRace; }
            long bestLapTimeMs() { return _bestLap; }
            long lastLapTimeMs() { return _lastLapTime; }
            long timeOfDayMs() { return _timeOfDayProgression; }
            short startPosition() { return _preRaceStartPos; }
            short calculatedMaxSpeed() { return _calculatedMaxSpeed; }
            float transmissionMaxSpeed() { return _transmissionMaxSpeed; }
            uint8_t currentGear() { return _currentGear; }
            uint8_t suggestedGear() { return _suggestedGear; }
            uint8_t throttlePosition() { return _throttle; }
            uint8_t brakePosition() { return _brake; }
            float clutchPedalPosition() { return _clutchPedal; }
            float clutchEngagement() { return _clutchEngagement; }
            float rpmFromClutchToGearbox() { return _rpmFromClutchToGearbox; }
            uint8_t unknown() { return _empty_0x93; }

        private:
            uint32_t _packetId;
            uint32_t _carId; // this value may get overriden if using a car that has 9 or more gears
            uint64_t _receivedTimestamp;

            float _orientationToNorth;
            float _bodyHeight;
            float _engineRPM;
            float _gasLevel;
            float _gasCapacity;
            float _carSpeed; 
            float _turboBoost;
            float _oilPressure;
            float _waterTemp;
            float _oilTemp;
            float _roadPlaneDistance;
            short _lapCount;
            short _lapsInRace;
            long _bestLap; // in milliseconds. Defaults to -1 if not set
            long _lastLapTime; // in milliseconds. Defaults to -1 if not set
            long _timeOfDayProgression; // in milliseconds. Time of day since midnight
            short _preRaceStartPos; // set to -1 after race starts
            short _nCarsInRace;
            short _calculatedMaxSpeed;
            float _transmissionMaxSpeed; // (as a gear ratio value)
            uint8_t _currentGear;
            uint8_t _suggestedGear;
            uint8_t _throttle;
            uint8_t _brake;
            float _clutchPedal;
            float _clutchEngagement;
            float _rpmFromClutchToGearbox;

            uint8_t _empty_0x93;

            Flags _flags;
            Bounds _alertRPM;
            GearRatios _gearRatios;
            Wheels _wheelsSurfaceTemp; 
            Wheels _wheelsRevs;
            Wheels _wheelsRadious;
            Wheels _suspentionHeight;
            Vector _position;
            Vector _velocity;
            Vector _rotation;
            Vector _angularVelocity;
            Vector _roadPlane;

            long unpackLong(const char* buffer, int* index);
            int unpackInt(const char* buffer, int* index);
            short unpackShort(const char* buffer, int* index);
            uint8_t unpackByte(const char* buffer, int* index);
            float unpackFloat(const char* buffer, int* index);            
            Vector unpackVector(const char* buffer, int* index);
            Wheels unpackWheels(const char* buffer, int* index);
            Flags unpackFlags(const char* buffer, int* index);
            Bounds unpackBounds(const char* buffer, int* index);
            GearRatios unpackGearRatios(const char* buffer, int* index);
    };
}

#endif