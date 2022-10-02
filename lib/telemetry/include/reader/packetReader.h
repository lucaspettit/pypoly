#ifndef SNAP_UDP_CLIENT_SERVER_H
#define SNAP_UDP_CLIENT_SERVER_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdexcept>
#include <string>
#include <time.h>

#pragma once

namespace gt {
    class PacketReader {
        public:
            PacketReader(const std::string& psAddr, int heartbeatPort, int telemetryPort);
            ~PacketReader();

            int recv(char *msg, size_t max_size);

        private:
            // const
            const unsigned char message[1] = {(unsigned char) 'A'};
            const int heartbeatPort;
            const int telemetryPort;
    
            // delay in seconds
            static const int heartbeatDelay = 10;

            struct timeval timeout;
            int sock;
            long lastHeartbeatTime;
            sockaddr_in addrOut;
            addrinfo addrHints, *addrRes;
            std::string psAddr;

            int packetCount = 0;

            // functions
            void sendHeartbeat();
        };

    }
#endif