#include "headers/protocol.h"

ServerProtocol::ServerProtocol(Socket peer): Protocol(std::move(peer)) {}


Command::ActionType ServerProtocol::receive_command() {
    unsigned char code = receiveUChar();
    return static_cast<Command::ActionType>(code);
}

void ServerProtocol::send_state(State::StateType state) { sendUChar(state); }

void ServerProtocol::send_datos_objeto(Contenedor c) {
    bool was_closed;
    int id = c.id();
    float x = c.posx();
    float y = c.posy();
    float w = c.width();
    float h = c.height();
    bool borrar = c.borrar();
    socket.sendall(&id, sizeof(id), &was_closed);
    socket.sendall(&x, sizeof(x), &was_closed);
    socket.sendall(&y, sizeof(y), &was_closed);
    socket.sendall(&w, sizeof(w), &was_closed);
    socket.sendall(&h, sizeof(h), &was_closed);
    socket.sendall(&borrar, sizeof(borrar), &was_closed);
}

void ServerProtocol::stop() { Protocol::stop(); }

void ServerProtocol::close() { Protocol::close(); }
