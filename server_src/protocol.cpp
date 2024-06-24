#include "headers/protocol.h"

ServerProtocol::ServerProtocol(Socket peer): Protocol(std::move(peer)) {}


//////////////SEND

void ServerProtocol::send_container(const Container& container) {
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
            std::cout << "Envio el: 1" << std::endl;
            send32(setupContainer.maxPlayers);
            std::cout << "Envio el: 2" << std::endl;
            sendString(setupContainer.mapName);
            std::cout << "Envio el: 3" << std::endl;
            send32(setupContainer.cheats.size());
            for (uint32_t i = 0; i < setupContainer.cheats.size(); i++) {
                send32(setupContainer.cheats[i]);
            }
            std::cout << "Envio el: 4" << std::endl;
            break;
        case Setup::ActionType::GET_GAME_LIST:
            sendBool(setupContainer.ok);
            sendVectorString(setupContainer.gameList);
            break;
        case Setup::ActionType::CLIENT_ID:
            sendBool(setupContainer.ok);
            send32(setupContainer.clientId);
            break;
        case Setup::ActionType::CREATE_MAP:
            sendBool(setupContainer.ok);
            sendMap(setupContainer.map);
            break;

        case Setup::ActionType::SAVE_MAP:
            sendBool(setupContainer.ok);
            break;

        case Setup::ActionType::SET_NAME:
            sendBool(setupContainer.ok);
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
        GameData data {
            gameContainer.id,
            gameContainer.x,
            gameContainer.y,
            gameContainer.w,
            gameContainer.h,
            gameContainer.direction,
            gameContainer.an_type,
            gameContainer.en_type,
            gameContainer.health,
            gameContainer.ammo,
            gameContainer.score,
        };
        
        bool was_closed;
        int msg_code = gameContainer.msg_code;

        socket.sendall(&msg_code, sizeof(msg_code), &was_closed);
        socket.sendall(&data, sizeof(data), &was_closed);
        sendString(gameContainer.name);
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
    std::cout << actionType << std::endl;
    switch (actionType) {
        case Setup::ActionType::CREATE_GAME:
            return receive_create_game();
        case Setup::ActionType::JOIN_GAME:
            return receive_join_game();
        case Setup::ActionType::GET_GAME_LIST:
            return receive_get_game_list();
        case Setup::ActionType::CREATE_MAP:
            return receive_create_map();
        case Setup::ActionType::SAVE_MAP:
            return receive_save_map();
        case Setup::ActionType::SET_NAME:
            return receive_set_name();
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
    std::string mapName = receiveString();
    uint32_t nCheats = receiveUInt32();
    std::vector<uint32_t> cheats;
    for (uint32_t i = 0; i < nCheats; i++) {
        cheats.insert(cheats.end(), receiveUInt32());
    }
    return Message(Setup::ActionType::CREATE_GAME, gameId, maxPlayers, mapName, cheats);
}

Message ServerProtocol::receive_create_map() {
    std::cout << "Recibiendo mensaje de create map\n";
    std::string mapName = receiveString();

    return Message(Setup::ActionType::CREATE_MAP, mapName);
}


Message ServerProtocol::receive_save_map() {
    std::cout << "Recibiendo mensaje de mapa guardado\n";
    std::string mapName = receiveString();
    std::vector<std::vector<std::string>> map = receiveMap();

    return Message(Setup::ActionType::SAVE_MAP, mapName, map);
}

Message ServerProtocol::receive_set_name() {
    std::string ClientName = receiveString();

    return Message(Setup::ActionType::SET_NAME, ClientName);
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
