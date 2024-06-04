#include "headers/client.h"

Client::Client(const std::string& hostname, const std::string& servername, Queue<Contenedor>& queue,
               SdlWindow& window, std::map<int, Entity*>& entidades):
        client_protocol(hostname.c_str(), servername.c_str()),
        client_receiver(client_protocol, queue),
        event_handler(client_protocol),
        updater(client_protocol, window, entidades, queue),
        online(false) {
            updater.agregar_cliente(this);
        }

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

void Client::set_id(int i) {
    id = i;
}

int Client::get_id() {
    return id;
}

void Client::close() {
    this->client_protocol.stop();

    this->event_handler.close();
    this->event_handler.join();

    // this->client_receiver.close();
    this->client_receiver.join();

    this->updater.close();
    this->updater.join();
}
