#include "protocol.h"

ClientProtocol::ClientProtocol(const char* hostname, const char* servicename):
        Protocol(std::move(Socket(hostname, servicename))) {}

void ClientProtocol::send_command(const Command& cmd) {
    unsigned char value = static_cast<unsigned char>(cmd.action);
    sendUChar(value);
}

void ClientProtocol::stop() { Protocol::stop(); }

