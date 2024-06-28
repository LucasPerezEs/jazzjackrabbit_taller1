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
            send32(setupContainer.maxPlayers);
            sendString(setupContainer.mapName);
            send32(setupContainer.cheats.size());
            for (uint32_t i = 0; i < setupContainer.cheats.size(); i++) {
                send32(setupContainer.cheats[i]);
            }
            break;
        case Setup::ActionType::GET_GAME_LIST:
            sendBool(setupContainer.ok);
            sendVectorString(setupContainer.gameList);
            break;
        case Setup::ActionType::GET_MAP_LIST:
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

        case Setup::ActionType::SET_NAME:
            sendBool(setupContainer.ok);
            break;

        default:
            throw std::runtime_error("Unknown setup action type to send");
    }
}


void ServerProtocol::send_game_container(const GameContainer& gameContainer) {

    if (gameContainer.msg_code == 2) {
        int msg_code = gameContainer.msg_code;
        int id = gameContainer.id;
        send32(msg_code);
        send32(id);

    } else {
        GameData data{
                gameContainer.id,      gameContainer.x,       gameContainer.y,
                gameContainer.w,       gameContainer.h,       gameContainer.direction,
                gameContainer.an_type, gameContainer.en_type, gameContainer.health,
                gameContainer.ammo,    gameContainer.score,
        };

        int msg_code = gameContainer.msg_code;

        send32(msg_code);
        sendGameData(data);
        sendString(gameContainer.name);
    }
}

void ServerProtocol::send_sound_container(const SoundContainer& soundContainer) {
    SoundData data;
    data.entity = soundContainer.entity;
    data.sound = soundContainer.sound;
    data.id = soundContainer.id;

    sendSoundData(data);
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
        default: {
            throw std::runtime_error("Unknown message type");
        }
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
        case Setup::ActionType::GET_MAP_LIST:
            return receive_get_map_list();
        case Setup::ActionType::CREATE_MAP:
            return receive_create_map();
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
    std::string mapName = receiveString();

    return Message(Setup::ActionType::CREATE_MAP, mapName);
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

Message ServerProtocol::receive_get_map_list() {
    // No additional data needed for GET_GAME_LIST setup
    return Message(Setup::ActionType::GET_MAP_LIST);
}


void ServerProtocol::stop() { Protocol::stop(); }

void ServerProtocol::close() { Protocol::close(); }
