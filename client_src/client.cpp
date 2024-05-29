#include "headers/client.h"

Client::Client(const std::string& hostname, const std::string& servername, Player& player,
               Queue<Contenedor>& queue, SdlWindow& window,
               std::vector<std::vector<float>>& objetos):
        client_protocol(hostname.c_str(), servername.c_str()),
        client_receiver(client_protocol, queue),
        event_handler(client_protocol, player),
        updater(client_protocol, window, objetos, queue),
        player(player),
        online(false) {}

void Client::go_online() {

    online = true;

    this->event_handler.start();
    this->updater.start();
    this->client_receiver.start();
}

bool Client::is_online() {
    online = event_handler.is_running();
    return online;
}


void Client::close() {
    this->client_protocol.stop();
    std::cout << "Cierro el protocolo" << std::endl;

    this->event_handler.close();
    this->event_handler.join();
    std::cout << "Cierro el handler" << std::endl;

    // this->client_receiver.close();
    this->client_receiver.join();
    std::cout << "Cierro el reciever" << std::endl;

    this->updater.close();
    this->updater.join();
    std::cout << "Cierro el updater" << std::endl;
}
