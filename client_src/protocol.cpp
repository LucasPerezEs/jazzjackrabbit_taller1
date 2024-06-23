#include "headers/protocol.h"

ClientProtocol::ClientProtocol(const std::string& hostname, const std::string& servicename):
        Protocol(Socket(hostname.c_str(), servicename.c_str())) {}


//////////////SEND

void ClientProtocol::send_message(const Message& message) {

    if (message.type() == Message::Type::SETUP) {
        sendUChar(static_cast<unsigned char>(message.type()));
        send_setup(message.setup);
    }

    if (message.type() == Message::Type::COMMAND) {
        sendUChar(static_cast<unsigned char>(message.type()));
        send_command(message.command);
    }
}

void ClientProtocol::send_command(const Command& cmd) {
    sendUChar(static_cast<unsigned char>(cmd.action));
}

void ClientProtocol::send_setup(const Setup& setup) {

    if (setup.action == Setup::ActionType::CREATE_GAME) {
        send_create_game(setup.gameId, setup.maxPlayers, setup.cheats);
    }

    if (setup.action == Setup::ActionType::JOIN_GAME) {
        send_join_game(setup.gameId, setup.character);
    }

    if (setup.action == Setup::ActionType::GET_GAME_LIST) {
        send_get_game_list();
    }

    if (setup.action == Setup::ActionType::CREATE_MAP) {
        send_create_map(setup.mapName);
    }

    if (setup.action == Setup::ActionType::SAVE_MAP) {
        send_save_map(setup.mapName, setup.map);
    }

    if (setup.action == Setup::ActionType::SET_NAME) {
        std::cout << "Enviando set name\n";
        send_set_name(setup.mapName);
    }
}


void ClientProtocol::send_join_game(const std::string& gameId, const int character) {
    sendUChar(static_cast<unsigned char>(Setup::JOIN_GAME));
    sendString(gameId);
    send32(character);
}

void ClientProtocol::send_create_game(const std::string& gameId, const uint32_t& maxPlayers,
                                      const std::vector<uint32_t>& cheats) {
    sendUChar(static_cast<unsigned char>(Setup::CREATE_GAME));
    sendString(gameId);
    send32(maxPlayers);
    send32(cheats.size());
    for (uint32_t i = 0; i < cheats.size(); i++) {
        send32(cheats[i]);
    }
}

void ClientProtocol::send_save_map(const std::string& mapName,
                                   const std::vector<std::vector<std::string>>& map) {
    sendUChar(static_cast<unsigned char>(Setup::SAVE_MAP));
    sendString(mapName);
    sendMap(map);

    std::cout << "Mande el mapa creado" << std::endl;
}

void ClientProtocol::send_create_map(const std::string& mapName) {
    sendUChar(static_cast<unsigned char>(Setup::CREATE_MAP));
    sendString(mapName);
}

void ClientProtocol::send_get_game_list() {
    sendUChar(static_cast<unsigned char>(Setup::GET_GAME_LIST));
}

void ClientProtocol::send_set_name(const std::string& clientName) {
    sendUChar(static_cast<unsigned char>(Setup::SET_NAME));
    sendString(clientName);
}

//////////////RECEIVE

Container ClientProtocol::receive_container() {
    unsigned char containerType = receiveUChar();
    Container::Type type = static_cast<Container::Type>(containerType);

    switch (type) {
        case Container::Type::SETUP:
            return receive_setup_container();
        case Container::Type::GAME:
            return receive_game_container();
        case Container::Type::SOUND:
            return receive_sound_container();
        default:
            throw std::runtime_error("Unknown message type");
    }
}

Container ClientProtocol::receive_setup_container() {
    unsigned char setupType = receiveUChar();
    Setup::ActionType actionType = static_cast<Setup::ActionType>(setupType);

    switch (actionType) {
        case Setup::ActionType::CREATE_GAME:
            return receive_create_game();
        case Setup::ActionType::JOIN_GAME:
            return receive_join_game();
        case Setup::ActionType::GET_GAME_LIST:
            return receive_get_game_list();
        case Setup::ActionType::CLIENT_ID:
            return receive_client_id();
        case Setup::ActionType::CREATE_MAP:
            return receive_create_map();
        case Setup::ActionType::SAVE_MAP:
            return receive_saved_map();
        case Setup::ActionType::SET_NAME:
            return receive_saved_name();
        default:
            throw std::runtime_error("Unknown setup action type");
    }
}

Container ClientProtocol::receive_create_game() {
    bool ok = receiveBool();
    std::cout << "recibo en el protocolo create game con resultado " << ok << "\n";
    std::string gameId = receiveString();
    uint32_t maxPlayers = receiveUInt32();
    uint32_t nCheats = receiveUInt32();
    std::vector<uint32_t> cheats;
    for (uint32_t i = 0; i < nCheats; i++) {
        cheats.insert(cheats.end(), receiveUInt32());
    }

    return Container(Setup::ActionType::CREATE_GAME, gameId, maxPlayers, cheats, ok);
}

Container ClientProtocol::receive_saved_map() {
    bool ok = receiveBool();
    return Container(Setup::ActionType::SAVE_MAP, ok);
}

Container ClientProtocol::receive_saved_name() {
    bool ok = receiveBool();
    return Container(Setup::ActionType::SET_NAME, ok);
}

Container ClientProtocol::receive_join_game() {
    bool ok = receiveBool();
    std::string gameId = receiveString();
    uint32_t maxPlayers = receiveUInt32();
    uint32_t nCheats = receiveUInt32();
    std::vector<uint32_t> cheats;
    for (uint32_t i = 0; i < nCheats; i++) {
        cheats.insert(cheats.end(), receiveUInt32());
    }
    std::cout << maxPlayers << std::endl;
    return Container(Setup::ActionType::JOIN_GAME, gameId, maxPlayers, cheats, ok);
}

Container ClientProtocol::receive_get_game_list() {
    bool ok = receiveBool();
    std::vector<std::string> gameList = receiveVectorString();
    return Container(Setup::ActionType::GET_GAME_LIST, gameList, ok);
}

Container ClientProtocol::receive_client_id() {
    bool ok = receiveBool();
    uint32_t id = receiveUInt32();
    return Container(Setup::ActionType::CLIENT_ID, id, ok);
}


Container ClientProtocol::receive_game_container() {
    bool was_closed;
    int msg_code;

    socket.recvall(&msg_code, sizeof(msg_code), &was_closed);

    if (msg_code == 2) {
        int id;
        socket.recvall(&id, sizeof(id), &was_closed);
        AmmoData data = {EntityType::NONE_ENTITY, 0};
        Container c(msg_code, id, 0, 0, 0, 0, 0, AnimationType::NONE_ANIMATION,
                    EntityType::NONE_ENTITY, 0, data, 0, "");
        return c;
    }

    GameData data;
    socket.recvall(&data, sizeof(data), &was_closed);

    std::string name = receiveString();

    Container c(msg_code, data.id, data.x, data.y, data.width, data.height, data.direction, data.an,
                data.en, data.health, data.ammo, data.score, name);
    return c;
}

Container ClientProtocol::receive_sound_container() {
    bool was_closed;
    SoundData data;

    socket.recvall(&data, sizeof(data), &was_closed);
    Container c(data.entity, data.sound, data.id);
    return c;
}

Container ClientProtocol::receive_create_map() {
    bool ok = receiveBool();
    std::vector<std::vector<std::string>> mapReceived = receiveMap();

    return Container(Setup::ActionType::CREATE_MAP, mapReceived, ok);
}

void ClientProtocol::stop() { Protocol::stop(); }
