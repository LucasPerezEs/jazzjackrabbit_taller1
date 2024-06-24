#include "headers/client.h"

Client::Client(const std::string& hostname, const std::string& servername):
        client_protocol(hostname.c_str(), servername.c_str()), online(false) {
    Container c = client_protocol.receive_container();
    id = c.setup_container->clientId;
    std::cout << "Se esta seteando el id del cliente que es: " << id << "\n";
}

void Client::go_online() {

    online = true;
}

bool Client::is_online() { return online; }

int Client::get_id() { return id; }

void Client::close() {
    this->client_protocol.stop();
}

std::vector<std::vector<std::string>> Client::getMap(){
    return map;   
}

bool Client::createGame(const std::string& gameId, const std::string& mapName, const uint32_t maxPlayers,
                        const std::vector<uint32_t>& cheats) {

    Message msg(Setup::ActionType::CREATE_GAME, gameId, maxPlayers, mapName, cheats);
    client_protocol.send_message(msg);
    Container container = client_protocol.receive_container();
    while (container.setup_container.get() == NULL || container.setup_container->setupType != Setup::ActionType::CREATE_GAME) {
        container = client_protocol.receive_container();
    }
    return container.setup_container->ok;
}

bool Client::joinGame(const std::string& gameId, const int character) {

    Message msg(Setup::ActionType::JOIN_GAME, character, gameId);
    client_protocol.send_message(msg);

    Container container = client_protocol.receive_container();
    map = container.setup_container->map;

    Container container2 = client_protocol.receive_container();

    if(container.setup_container->ok == true && container2.setup_container->ok == true){
        return true;
    } else {
        return false;
    }

}

bool Client::saveMap(const std::string& mapName, std::vector<std::vector<std::string>>& mapSended){

    std::cout << "Estoy en client createMap para guardar el mapa" << std::endl;

    Message msg(Setup::ActionType::SAVE_MAP, mapName, mapSended);
    client_protocol.send_message(msg);

    std::cout << "Se envio el mensaje de guardado" << std::endl;
    Container container = client_protocol.receive_container();

    std::cout << "Se recibe el container de envios?" << std::endl;

    return container.setup_container->ok;
}

bool Client::refreshGameList(std::vector<std::string>& gameList) {
    Message msg(Setup::ActionType::GET_GAME_LIST);
    client_protocol.send_message(msg);
    // recibir gamelist
    Container container = client_protocol.receive_container();
    while (container.setup_container.get() == NULL || container.setup_container->setupType != Setup::ActionType::GET_GAME_LIST) {
        container = client_protocol.receive_container();
    }

    gameList = container.setup_container->gameList;

    return container.setup_container->ok;
}

bool Client::setName(const std::string& clientName) {
    Message msg(Setup::ActionType::SET_NAME, clientName);
    client_protocol.send_message(msg);

    Container container = client_protocol.receive_container();

    return container.setup_container->ok;
}

ClientProtocol& Client::get_protocol() { return client_protocol; }
