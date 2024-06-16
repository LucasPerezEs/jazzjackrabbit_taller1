#include "headers/protocol.h"

ServerProtocol::ServerProtocol(Socket peer): Protocol(std::move(peer)) {}


Command::ActionType ServerProtocol::receive_command() {
    unsigned char code = receiveUChar();
    return static_cast<Command::ActionType>(code);
}


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

Message ServerProtocol::receive_message(){
    unsigned char type = receiveUChar();
    Message::Type messageType = static_cast<Message::Type>(type);

    switch (messageType) {
        case Message::Type::SETUP:
            return receive_setup_message();
        case Message::Type::COMMAND:
            return receive_command_message();
        default:
            throw std::runtime_error("Unknown message type");
    }

}

Message ServerProtocol::receive_setup_message() {
    unsigned char setupType = receiveUChar();
    Setup::ActionType actionType = static_cast<Setup::ActionType>(setupType);

    switch (actionType) {
        case Setup::ActionType::CREATE_GAME:
            return receive_create_game();
        case Setup::ActionType::JOIN_GAME:
            return receive_join_game();
        case Setup::ActionType::GET_GAME_LIST:
            return receive_get_game_list();
        default:
            throw std::runtime_error("Unknown setup action type");
    }
}

Message ServerProtocol::receive_command_message() {
    unsigned char commandType = receiveUChar();
    Command::ActionType actionType = static_cast<Command::ActionType>(commandType);

    return Message(actionType);
}

Message ServerProtocol::receive_create_game() {
    std::string gameId = receiveString();
    uint32_t maxPlayers = receiveUInt32();
    return Message(Setup::ActionType::CREATE_GAME,gameId,maxPlayers);
}

Message ServerProtocol::receive_join_game() {
    std::string gameId = receiveString();
    return Message(Setup::ActionType::JOIN_GAME, gameId);
}

Message ServerProtocol::receive_get_game_list() {
    // No additional data needed for GET_GAME_LIST setup
    return Message(Setup::ActionType::GET_GAME_LIST);
}


void ServerProtocol::send_games_ids(const std::vector<std::string>& gameIDs) {
    //send_vector_string(gameIDs);
}