#include "../../include/models/packet.h"
#include <exception>

namespace gt {
    Packet::Packet(const char* buffer, int size) {
        if(size != 296) {
            std::invalid_argument("Invalid buffer size");
        }
        int index = 4;
        _position = Packet::unpackVector(buffer, &index);
        _velocity = Packet::unpackVector(buffer, &index);
        _rotation = Packet::unpackVector(buffer, &index);
        _orientationToNorth = Packet::unpackFloat(buffer, &index);
        _angularVelocity = Packet::unpackVector(buffer, &index);
        _bodyHeight = Packet::unpackFloat(buffer, &index);
        _engineRPM = Packet::unpackFloat(buffer, &index);

        // this byte is unused ? 
        index += 4; 
        
        _gasLevel = Packet::unpackFloat(buffer, &index);
        _gasCapacity = Packet::unpackFloat(buffer, &index);
        _carSpeed = Packet::unpackFloat(buffer, &index);
        _turboBoost = Packet::unpackFloat(buffer, &index);
        _oilPressure = Packet::unpackFloat(buffer, &index);
        _waterTemp = Packet::unpackFloat(buffer, &index);
        _oilTemp = Packet::unpackFloat(buffer, &index);
        _wheelsSurfaceTemp = Packet::unpackWheels(buffer, &index);
        _packetId = Packet::unpackInt(buffer, &index);
        _lapCount = Packet::unpackByte(buffer, &index);
        _lapsInRace = Packet::unpackByte(buffer, &index);
        _bestLap = Packet::unpackInt(buffer, &index);
        _lastLapTime = Packet::unpackInt(buffer, &index);
        _timeOfDayProgression = Packet::unpackInt(buffer, &index);
        _preRaceStartPos = Packet::unpackByte(buffer, &index);
        _nCarsInRace = Packet::unpackByte(buffer, &index);
        _alertRPM = Packet::unpackBounds(buffer, &index);
        _calculatedMaxSpeed = Packet::unpackShort(buffer, &index);
        _flags = Packet::unpackFlags(buffer, &index);

        // get current & suggested gears
        uint8_t byte = Packet::unpackByte(buffer, &index);
        _currentGear = byte & 15;
        _suggestedGear = byte >> 4;

        _throttle = Packet::unpackByte(buffer, &index);
        _brake = Packet::unpackByte(buffer, &index);
        _empty_0x93 = Packet::unpackByte(buffer, &index);
        _roadPlane = Packet::unpackVector(buffer, &index);
        _roadPlaneDistance = Packet::unpackFloat(buffer, &index);
        _wheelsRevs = Packet::unpackWheels(buffer, &index);
        _wheelsRadious = Packet::unpackWheels(buffer, &index);
        _suspentionHeight = Packet::unpackWheels(buffer, &index);

        // this byte is unused ? 
        index += 32; 
        
        _clutchPedal = Packet::unpackFloat(buffer, &index);
        _clutchEngagement = Packet::unpackFloat(buffer, &index);
        _rpmFromClutchToGearbox = Packet::unpackFloat(buffer, &index);
        _transmissionMaxSpeed = Packet::unpackFloat(buffer, &index);
        _gearRatios = Packet::unpackGearRatios(buffer, &index);
        _carId = Packet::unpackInt(buffer, &index);
    }

    long Packet::unpackLong(const char* buffer, int* index) {
        long value = *(long*) &buffer[*index];
        (*index) += 8;
        return value;
    }

    int Packet::unpackInt(const char* buffer, int* index) {
        int value = *(int*) &buffer[*index];
        (*index) += 4;
        return value;
    }

    short Packet::unpackShort(const char* buffer, int* index) {
        short value = *(short*) &buffer[*index];
        (*index) += 2;
        return value;
    }

    uint8_t Packet::unpackByte(const char* buffer, int* index) {
        uint8_t value = *(uint8_t*) &buffer[*index];
        (*index) += 2;
        return value;
    }

    float Packet::unpackFloat(const char* buffer, int* index) {
        float value = *(float*) &buffer[*index];
        (*index) += 4;
        return value;
    }

    Vector Packet::unpackVector(const char* buffer, int* index) {
        return Vector(
            Packet::unpackFloat(buffer, index),
            Packet::unpackFloat(buffer, index),
            Packet::unpackFloat(buffer, index)
        );
    }

    Wheels Packet::unpackWheels(const char* buffer, int* index) {
        return Wheels(
            Packet::unpackFloat(buffer, index),
            Packet::unpackFloat(buffer, index),
            Packet::unpackFloat(buffer, index),
            Packet::unpackFloat(buffer, index)
        );
    }

    Bounds Packet::unpackBounds(const char* buffer, int* index) {
        return Bounds(
            Packet::unpackFloat(buffer, index),
            Packet::unpackFloat(buffer, index)
        );
    }

    Flags Packet::unpackFlags(const char* buffer, int* index) {
        Flags flags = Flags(buffer[*index]);
        (*index) += 2; // Note, Flags only uses 12-bits, so there's 4-bits unused
        return flags;
    }

    GearRatios Packet::unpackGearRatios(const char* buffer, int* index) {
        // For now, just assume 8 gears.. potentually 9 one day
        float gears[8];
        for(int i = 0; i < 8; i++) {
            gears[i] = Packet::unpackFloat(buffer, index);
        }
        return GearRatios(gears, 8);
    }
}