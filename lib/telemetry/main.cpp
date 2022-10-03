#include <iostream>
#include <iomanip>
#include <string>
#include "include/telemetryReader.h"
#include "include/models/packet.h"
#include "include/utils/debug.h"

using namespace std;
using namespace gt;

const string GREEN = "\u001b[32m";
const string RESET = "\u001b[0m";

const static Debug debug = Debug();
const string addr = "192.168.1.207";

int main() {
    cout << fixed;
    cout << "Starting program" << endl;
    TelemetryReader reader = TelemetryReader(addr);

    cout << "Starting main loop" << endl;
    while (true) {
        Packet packet = reader.getPacket();

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