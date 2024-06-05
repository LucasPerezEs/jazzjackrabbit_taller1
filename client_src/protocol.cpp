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


Contenedor ClientProtocol::receive_info() {
    bool was_closed = false;
    int msg_code;
    socket.recvall(&msg_code, sizeof(msg_code), &was_closed);
    if (msg_code == 2) {
        int id;
        socket.recvall(&id, sizeof(id), &was_closed);
        Contenedor c(msg_code, id, 0, 0, 0, 0, 0, AnimationType::NONE_ANIMATION,
                     EntityType::NONE_ENTITY, 0, 0, 0);
        return c;
    } else {
        Contenedor aux = receiveDatosObjeto();
        Contenedor c(msg_code, aux.id(), aux.posx(), aux.posy(), aux.width(), aux.height(),
                     aux.direccion(), aux.animation_type(), aux.entity_type(), aux.vida(),
                     aux.municion(), aux.score());
        return c;
    }
}

Contenedor ClientProtocol::receiveDatosObjeto() {

    int id;
    float x;
    float y;
    float w;
    float h;
    int direccion;
    AnimationType an;
    EntityType en;
    bool was_closed = false;
    int vida;
    int municion;
    int score;

    socket.recvall(&id, sizeof(id), &was_closed);
    socket.recvall(&x, sizeof(x), &was_closed);
    socket.recvall(&y, sizeof(y), &was_closed);
    socket.recvall(&w, sizeof(w), &was_closed);
    socket.recvall(&h, sizeof(h), &was_closed);
    socket.recvall(&direccion, sizeof(direccion), &was_closed);
    socket.recvall(&an, sizeof(an), &was_closed);
    socket.recvall(&en, sizeof(en), &was_closed);
    socket.recvall(&vida, sizeof(vida), &was_closed);
    socket.recvall(&municion, sizeof(municion), &was_closed);
    socket.recvall(&score, sizeof(score), &was_closed);

    Contenedor c(0, id, x, y, w, h, direccion, an, en, vida, municion, score);
    return c;
}

void ClientProtocol::stop() { Protocol::stop(); }
