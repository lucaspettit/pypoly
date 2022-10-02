#include <iostream>
#include <iomanip>
#include <string>
#include "../include/receiver.h"
#include "../include/cipher/cipher.h"
#include "../include/models/packet.h"
#include "../include/utils/debug.h"

using namespace std;
using namespace gt;

const string GREEN = "\u001b[32m";
const string RESET = "\u001b[0m";

const static utils::Debug debug = utils::Debug();

const std::string addr = "192.168.1.207";
const int heartbeatPort = 33739;
const int telemetryPort = 33740;
const int bufferSize = 0x128;
char rawBuffer[bufferSize] = {0};
char decryptedBuffer[bufferSize] = {0};


int main() {
    cout << fixed;
    cout << "Starting program" << endl;

    cout << "Initializing UDP socket...";
    UdpConnector psConnector = UdpConnector(addr, heartbeatPort, telemetryPort);
    cout << GREEN << "DONE" << RESET << endl;
    
    cout << "Initializing Cipher...";
    Cipher cipher = Cipher();
    cout << GREEN << "DONE" << RESET << endl;

    cout << "Starting main loop" << endl;
    while (true) {
        int bytesReceived = psConnector.recv(rawBuffer, bufferSize);
        if (bytesReceived != 296) {
            cerr << "ERROR: Did not receive expected number of bytes. actual:[" << bytesReceived << "] expected:[" << 296 << "]" << endl;
            continue;
        }

        if(cipher.decrypt(rawBuffer, decryptedBuffer, bufferSize) != 0) {
            cerr << "ERROR: Unable to decrypt packet" << endl;
            continue; 
        }

        Packet packet = Packet(decryptedBuffer, 296);

        cout << "packetId:[" << packet.packetId() << "] timestamp:[" << packet.receivedTimestamp() << "]" << endl;
        Vector pos = packet.position();
        cout << "    position:(" << pos.x() << ", " << pos.y() << ", " << pos.z() << ")" << endl;
        Vector vel = packet.velocity();
        cout << "    velocity:(" << vel.x() << ", " << vel.y() << ", " << vel.z() << ")" << endl;
        Vector rot = packet.rotation();
        cout << "    rotation:(" << rot.x() << ", " << rot.y() << ", " << rot.z() << ")" << endl;
        Vector angvel = packet.angularVelocity();
        cout << "    angularVelocity:(" << angvel.x() << ", " << angvel.y() << ", " << angvel.z() << ")" << endl;
        cout << "    orientation:[" << packet.orientation() << "]" << endl;
        cout << "    carSpeed:[" << packet.carSpeed() << "]" << endl;
        cout << "    engineRPM:[" << packet.engineRPM() << "]" << endl;
        cout << "    bodyHeight:[" << packet.bodyHeight() << "]" << endl;
        Wheels sus = packet.suspentionHeight();
        cout << "    suspensionHeight: FL:[" << sus.frontLeft() << "] FR:[" << sus.frontRight() 
            << "] RL:[" << sus.rearLeft() << "] RR:[" << sus.rearRight() << "]" << endl;
    }
}