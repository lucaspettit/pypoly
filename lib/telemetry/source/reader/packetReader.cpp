#include "../../include/receiver.h"
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <ostream>
#include <arpa/inet.h>
#include <string>

namespace gt {

PacketReader::PacketReader(
    const std::string& psAddr, 
    int heartbeatPort,
    int telemetryPort): 
    heartbeatPort(heartbeatPort), 
    telemetryPort(telemetryPort), 
    psAddr(psAddr) {
    // setup attrOut. This is for the heartbeat addr info
    addrOut.sin_family = AF_INET;
    addrOut.sin_addr.s_addr = inet_addr(psAddr.c_str());
    addrOut.sin_port = htons(PacketReader::heartbeatPort);

    // setup hints & res for binding inbound socket
    memset(&addrHints, 0, sizeof(addrHints));
    addrHints.ai_family = AF_INET; //AF_UNSPEC; // use IPv4 or IPv6, whichever
    addrHints.ai_socktype = SOCK_DGRAM; // UDP
    addrHints.ai_flags = AI_PASSIVE; // wildcard IP
    std::string port = std::to_string(PacketReader::telemetryPort);
    int s = getaddrinfo(NULL, port.c_str(), &addrHints, &addrRes);
    if (s != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
        exit(EXIT_FAILURE);
    }

    // create socket and bind
    sock = socket(
        addrRes->ai_family, 
        addrRes->ai_socktype, 
        addrRes->ai_protocol); // IPPROTO_UDP
    bind(sock, addrRes->ai_addr, addrRes->ai_addrlen);

    // set socket timeout
    timeout.tv_sec = 100; // ms
    timeout.tv_usec = 0;
    setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
    lastHeartbeatTime = 0;
}

PacketReader::~PacketReader() {
    close(sock);
}

int PacketReader::recv(char *msg, size_t max_size) {
    sendHeartbeat();
    packetCount += 1;
    return ::recv(sock, msg, max_size, 0);
}

void PacketReader::sendHeartbeat() {
    // send heartbeat
    long currentTime = time(NULL); 
    if (currentTime - lastHeartbeatTime >= PacketReader::heartbeatDelay) {
        std::cout << "heartbeat:[" << psAddr << ":" << heartbeatPort << "]"
            << " tps:[" << (packetCount / (int)(currentTime - lastHeartbeatTime)) << "]" 
            << std::endl;
        packetCount = 0;
        
        int ret = sendto(
            sock, 
            message, 
            1, // message size 
            0, // flags (no flags)
            reinterpret_cast<sockaddr *>(&addrOut), 
            sizeof(addrOut));
        lastHeartbeatTime = currentTime;
    }
}

} // namespace udp 

// vim: ts=4 sw=4 et