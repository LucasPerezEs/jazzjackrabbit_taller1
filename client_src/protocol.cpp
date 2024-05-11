#include "protocol.h"

ClientProtocol::ClientProtocol(const std::string& hostname, const std::string& servicename):
        Protocol(std::move(Socket(hostname.c_str(), servicename.c_str()))) {}

void ClientProtocol::send_command(Command& cmd) {
    unsigned char value = static_cast<unsigned char>(cmd.action);
    sendUChar(value);
}

void ClientProtocol::stop() { Protocol::stop(); }

