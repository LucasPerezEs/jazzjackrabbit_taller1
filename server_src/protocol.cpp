#include "headers/protocol.h"

ServerProtocol::ServerProtocol(Socket peer): Protocol(std::move(peer)) {}


Command::ActionType ServerProtocol::receive_command() {
    unsigned char code = receiveUChar();
    return static_cast<Command::ActionType>(code);
}

void ServerProtocol::send_state(State::StateType state) { sendUChar(state); }

void ServerProtocol::stop() { Protocol::stop(); }

void ServerProtocol::close() { Protocol::close(); }
