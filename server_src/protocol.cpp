#include "headers/protocol.h"

ServerProtocol::ServerProtocol(Socket peer): Protocol(std::move(peer)) {}


Command::ActionType ServerProtocol::receive_command() {
    unsigned char code = receiveUChar();
    return static_cast<Command::ActionType>(code);
}

void ServerProtocol::send_state(State::StateType state) { sendUChar(state); }

void ServerProtocol::send_info(Contenedor c) {
    if (c.msg_code() == 2) {
        send_id(c);
    } else {
        send_datos_objeto(c);
    }
}

void ServerProtocol::send_id(Contenedor c) {
    bool was_closed;
    int msg_code = c.msg_code();
    int id = c.id();

    socket.sendall(&msg_code, sizeof(msg_code), &was_closed);
    socket.sendall(&id, sizeof(id), &was_closed);
}

void ServerProtocol::send_datos_objeto(Contenedor c) {
    bool was_closed;
    int msg_code = c.msg_code();
    int id = c.id();
    float x = c.posx();
    float y = c.posy();
    float w = c.width();
    float h = c.height();
    int direccion = c.direccion();
    AnimationType an_type = c.animation_type();
    EntityType en_type = c.entity_type();
    int vida = c.vida();
    int municion = c.municion();
    int score = c.score();

    socket.sendall(&msg_code, sizeof(msg_code), &was_closed);
    socket.sendall(&id, sizeof(id), &was_closed);
    socket.sendall(&x, sizeof(x), &was_closed);
    socket.sendall(&y, sizeof(y), &was_closed);
    socket.sendall(&w, sizeof(w), &was_closed);
    socket.sendall(&h, sizeof(h), &was_closed);
    socket.sendall(&direccion, sizeof(direccion), &was_closed);
    socket.sendall(&an_type, sizeof(an_type), &was_closed);
    socket.sendall(&en_type, sizeof(en_type), &was_closed);
    socket.sendall(&vida, sizeof(vida), &was_closed);
    socket.sendall(&municion, sizeof(municion), &was_closed);
    socket.sendall(&score, sizeof(score), &was_closed);
}

void ServerProtocol::stop() { Protocol::stop(); }

void ServerProtocol::close() { Protocol::close(); }

std::pair<Command::ActionType, uint32_t> ServerProtocol::receive_command_with_id() {
    unsigned char code = receiveUChar();
    uint32_t clientId =
            receiveUInt32();  // Suponiendo que el ID del cliente es un entero sin signo de 32 bits
    return std::make_pair(static_cast<Command::ActionType>(code), clientId);
}
