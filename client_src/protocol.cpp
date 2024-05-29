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
    SpecialAction::SpecialActionType actionType =
            static_cast<SpecialAction::SpecialActionType>(receivedSpecialAction);

    return {stateType, actionType};
}


Contenedor ClientProtocol::receiveDatosObjeto() {
    int msg_code;
    int id;
    float x;
    float y;
    float w;
    float h;
    bool borrar;
    bool was_closed = false;
    socket.recvall(&msg_code, sizeof(msg_code), &was_closed);
    socket.recvall(&id, sizeof(id), &was_closed);
    socket.recvall(&x, sizeof(x), &was_closed);
    socket.recvall(&y, sizeof(y), &was_closed);
    socket.recvall(&w, sizeof(w), &was_closed);
    socket.recvall(&h, sizeof(h), &was_closed);
    socket.recvall(&borrar, sizeof(borrar), &was_closed);

    Contenedor c(msg_code, id, x, y, w, h, borrar);
    return c;
}

void ClientProtocol::stop() { Protocol::stop(); }
