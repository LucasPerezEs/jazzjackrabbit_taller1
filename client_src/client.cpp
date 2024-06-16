#include "headers/client.h"

Client::Client(const std::string& hostname, const std::string& servername, Queue<Container>& queue,
               SdlWindow& window, std::map<int, Entity*>& entidades,
               std::map<int, Player*>& personajes, UIManager& ui_manager):
        client_protocol(hostname.c_str(), servername.c_str()),
        client_receiver(client_protocol, queue),
        event_handler(client_protocol),
        updater(client_protocol, window, entidades, queue, personajes, ui_manager),
        online(false) {
    updater.agregar_cliente(this);
}

void Client::go_online() {

    online = true;

    //se inicia una vez entrado al juego
    //this->event_handler.start();
    //this->updater.start();
    //this->client_receiver.start();
}

bool Client::is_online() {
    online = event_handler.is_running();
    return online;
}

void Client::set_id(int i) { id = i; }

int Client::get_id() { return id; }

void Client::close() {
    this->client_protocol.stop();

    this->event_handler.close();
    this->event_handler.join();

    // this->client_receiver.close();
    this->client_receiver.join();

    this->updater.close();
    this->updater.join();
}

bool Client::createGame(const std::string& gameId, const uint32_t maxPlayers) {
    Message msg(Setup::ActionType::CREATE_GAME,gameId,maxPlayers);
    client_protocol.send_message(msg);
    //recibir confirmacion
    return true;
}

bool Client::joinGame(const std::string& gameId) {


    Message msg(Setup::ActionType::JOIN_GAME,gameId);
    client_protocol.send_message(msg);
    //recibir confirmacion

    this->event_handler.start();
    this->updater.start();
    this->client_receiver.start();
    return true;

    //return false
}

std::vector<std::string> Client::refreshGameList() {
    Message msg(Setup::ActionType::GET_GAME_LIST);
    client_protocol.send_message(msg);
    //recibir gamelist
    return std::vector<std::string>();
}

EventHandler* Client::get_EventHandler() { return &event_handler; }
