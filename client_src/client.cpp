#include "headers/client.h"

Client::Client(const std::string& hostname, const std::string& servername, Player& player):
        client_protocol(hostname.c_str(), servername.c_str()),
        event_handler(client_protocol, player),
        updater(client_protocol),
        player(player),
        online(false) {}

void Client::go_online() {

    online = true;

    this->event_handler.start();
    this->updater.start();

}

bool Client::is_online() {
    online = event_handler.is_running() && updater.is_running();
    return online;
}



void Client::close() {
    this->client_protocol.stop();

    this->event_handler.close();
    this->event_handler.join();

    this->updater.close();
    this->updater.join();
}


