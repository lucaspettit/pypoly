#ifndef TELEMETRY_READER_H
#define TELEMETRY_READER_H

#include <iostream>
#include <iomanip>
#include <string>
#include "reader/packetReader.h"
#include "security/cipher.h"
#include "models/packet.h"
#include "utils/constants.h"

namespace gt {
    class TelemetryReader {
        public:
            TelemetryReader(std::string addr);
            ~TelemetryReader();

            /**
             * Returns the latest packet. If no new packet is available, this
             * function will wait until next available packet is received.
             */
            Packet getPacket();

        private:
            static Cipher cipher;
            PacketReader reader;
            char rawBuffer[BUFFER_SIZE];
            char decryptedBuffer[BUFFER_SIZE];

    };
}

#endif
