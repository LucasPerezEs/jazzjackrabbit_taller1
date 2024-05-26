#include "headers/protocol.h"

ClientProtocol::ClientProtocol(const std::string& hostname, const std::string& servicename):
        Protocol(std::move(Socket(hostname.c_str(), servicename.c_str()))) {}

void ClientProtocol::send_command(Command& cmd) {
    sendUChar(static_cast<unsigned char>(cmd.action));
}

std::pair<State::StateType, SpecialAction::SpecialActionType> ClientProtocol::receive_update() {
    unsigned char receivedState = receiveUChar();
    unsigned char receivedSpecialAction = receiveUChar();

    State::StateType stateType = static_cast<State::StateType>(receivedState);
    SpecialAction::SpecialActionType actionType = static_cast<SpecialAction::SpecialActionType>(receivedSpecialAction);

    return {stateType, actionType};
}

void ClientProtocol::stop() { Protocol::stop(); }
