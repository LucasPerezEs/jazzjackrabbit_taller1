#include "headers/protocol.h"

ServerProtocol::ServerProtocol(Socket peer): Protocol(std::move(peer)) {}


//////////////SEND

void ServerProtocol::send_container(const Container& container) {
    std::cout << "Enviando container\n";
    if (container.type() == Container::Type::SETUP) {
        sendUChar(static_cast<unsigned char>(container.type()));
        send_setup_container(*container.setup_container);
    }

    if (container.type() == Container::Type::GAME) {
        sendUChar(static_cast<unsigned char>(container.type()));
        send_game_container(*container.game_container);
    }

    if (container.type() == Container::Type::SOUND) {
        sendUChar(static_cast<unsigned char>(container.type()));
        send_sound_container(*container.sound_container);
    }
}

void ServerProtocol::send_setup_container(const SetupContainer& setupContainer) {
    std::cout << "\n";
    Setup::ActionType actionType = static_cast<Setup::ActionType>(setupContainer.setupType);
    sendUChar(actionType);

    switch (actionType) {
        case Setup::ActionType::CREATE_GAME:
            sendBool(setupContainer.ok);
            sendString(setupContainer.gameId);
            send32(setupContainer.maxPlayers);
            send32(setupContainer.cheats.size());
            for (uint32_t i = 0; i < setupContainer.cheats.size(); i++) {
                send32(setupContainer.cheats[i]);
            }
            break;
        case Setup::ActionType::JOIN_GAME:
            sendBool(setupContainer.ok);
            sendString(setupContainer.gameId);
            send32(setupContainer.maxPlayers);
            send32(setupContainer.cheats.size());
            for (uint32_t i = 0; i < setupContainer.cheats.size(); i++) {
                send32(setupContainer.cheats[i]);
            }
            break;
        case Setup::ActionType::GET_GAME_LIST:
            sendBool(setupContainer.ok);
            sendVectorString(setupContainer.gameList);
            break;
        case Setup::ActionType::CLIENT_ID:
            sendBool(setupContainer.ok);
            send32(setupContainer.clientId);
            break;
        default:
            throw std::runtime_error("Unknown setup action type to send");
    }
}


void ServerProtocol::send_game_container(const GameContainer& gameContainer) {

    if (gameContainer.msg_code == 2) {
        bool was_closed;
        int msg_code = gameContainer.msg_code;
        int id = gameContainer.id;
        socket.sendall(&msg_code, sizeof(msg_code), &was_closed);
        socket.sendall(&id, sizeof(id), &was_closed);
        std::cout << "enviando salida\n";

    } else {
        bool was_closed;
        int msg_code = gameContainer.msg_code;
        int id = gameContainer.id;
        float x = gameContainer.x;
        float y = gameContainer.y;
        float w = gameContainer.w;
        float h = gameContainer.h;
        int direccion = gameContainer.direction;
        AnimationType an_type = gameContainer.an_type;
        EntityType en_type = gameContainer.en_type;
        int vida = gameContainer.health;
        int municion = gameContainer.ammo;
        int score = gameContainer.score;

        socket.sendall(&msg_code, sizeof(msg_code), &was_closed);
        socket.sendall(&id, sizeof(id), &was_closed);
        socket.sendall(&x, sizeof(x), &was_closed);
        socket.sendall(&y, sizeof(y), &was_closed);  // esto hay que cambiarlo
        socket.sendall(&w, sizeof(w), &was_closed);
        socket.sendall(&h, sizeof(h), &was_closed);
        socket.sendall(&direccion, sizeof(direccion), &was_closed);
        socket.sendall(&an_type, sizeof(an_type), &was_closed);
        socket.sendall(&en_type, sizeof(en_type), &was_closed);
        socket.sendall(&vida, sizeof(vida), &was_closed);
        socket.sendall(&municion, sizeof(municion), &was_closed);
        socket.sendall(&score, sizeof(score), &was_closed);
    }
}

void ServerProtocol::send_sound_container(const SoundContainer& soundContainer) {
    bool was_closed;
    EntityType entity = soundContainer.entity;
    SoundType sound = soundContainer.sound;
    int id = soundContainer.id;
    socket.sendall(&entity, sizeof(entity), &was_closed);
    socket.sendall(&sound, sizeof(sound), &was_closed);
    socket.sendall(&id, sizeof(id), &was_closed);
}


//////////////RECEIVE


Message ServerProtocol::receive_message() {
    unsigned char type = receiveUChar();
    std::cout << "Recibiendo mensaje\n";
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
    std::cout << "Recibiendo mensaje de setup\n";
    unsigned char setupType = receiveUChar();
    Setup::ActionType actionType = static_cast<Setup::ActionType>(setupType);
    std::cout << actionType << std::endl;
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
    std::cout << "Recibiendo mensaje de create game\n";
    std::string gameId = receiveString();
    uint32_t maxPlayers = receiveUInt32();
    uint32_t nCheats = receiveUInt32();
    std::vector<uint32_t> cheats;
    for (uint32_t i = 0; i < nCheats; i++) {
        cheats.insert(cheats.end(), receiveUInt32());
    }
    return Message(Setup::ActionType::CREATE_GAME, gameId, maxPlayers, cheats);
}

Message ServerProtocol::receive_join_game() {
    std::string gameId = receiveString();
    uint32_t character = receiveUInt32();
    return Message(Setup::ActionType::JOIN_GAME, character, gameId);
}

Message ServerProtocol::receive_get_game_list() {
    // No additional data needed for GET_GAME_LIST setup
    return Message(Setup::ActionType::GET_GAME_LIST);
}


void ServerProtocol::send_games_ids(const std::vector<std::string>& gameIDs) {
    // send_vector_string(gameIDs);
}


void ServerProtocol::stop() { Protocol::stop(); }

void ServerProtocol::close() { Protocol::close(); }
