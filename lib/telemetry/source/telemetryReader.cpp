#include "../include/telemetryReader.h"
#include <exception>

using namespace std;

class TimeoutException: public exception {
    private:
        char* message;
    public:
        TimeoutException() {
            string msg = "Socket timeout";
            message = (char*) &msg;
        }
        char* what() {
            return message;
        }
};

class ReaderException : public exception {
    private:
        char* message;

    public:
        ReaderException(char * msg) : message(msg) {}
        char* what () {
            return message;
        }
};

gt::Cipher gt::TelemetryReader::cipher = gt::Cipher();

namespace gt {
    TelemetryReader::TelemetryReader(string addr)
        : reader(PacketReader(addr, HEARTBEAT_PORT, RECEIVE_PORT)) {
        memcpy(rawBuffer, 0, sizeof(rawBuffer));
        memcpy(decryptedBuffer, 0, sizeof(decryptedBuffer));
    }

    TelemetryReader::~TelemetryReader() {
        // TODO: fill me in when packet reader becomes threaded
    }

    Packet TelemetryReader::getPacket() {
        int bytesReceived = reader.recv(rawBuffer, BUFFER_SIZE);
        if (bytesReceived == -1) {
            throw TimeoutException();
        }
        if (bytesReceived != BUFFER_SIZE) {
            string msg = "Unexpected byte count. Actual:[" + to_string(bytesReceived)
                + "] Expected:[" + to_string(BUFFER_SIZE) + "]";
            throw ReaderException((char*) &msg);
        }
        if(cipher.decrypt(rawBuffer, decryptedBuffer, BUFFER_SIZE) != 0) {
            string msg = "Cannot decrypt packet";
            throw ReaderException((char*) &msg);
        }

        return Packet(decryptedBuffer, BUFFER_SIZE);
    }
}