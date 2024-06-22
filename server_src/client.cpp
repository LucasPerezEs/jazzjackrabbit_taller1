#include "headers/client.h"

ClientHandler::ClientHandler(uint32_t id, Socket peer):
        id(id),
        name(std::string()),
        serverProtocol(std::move(peer)),
        receiverThread(id, serverProtocol),
        senderThread(id, serverProtocol),
        online(true)
         {}

bool ClientHandler::is_online() { return online; }

void ClientHandler::kill() {

    online = false;

    if (senderThread.is_alive()) {
        senderThread.stop();
    }

    if (receiverThread.is_alive()) {
        receiverThread.stop();
    }

    serverProtocol.close();

    senderThread.close();
    senderThread.join();

    receiverThread.join();
}


void ClientHandler::go_online() {

    online = true;

    senderThread.start();
    receiverThread.start();
}

void ClientHandler::pushState(const Container& c) { senderThread.pushDatosObjeto(c); }

ClientHandler::~ClientHandler() {}


void ClientHandler::setReceiverQueue(Queue<Message>* actionQueue) {
    receiverThread.setQueue(actionQueue);
}


uint32_t ClientHandler::getId() { return id; }

std::string ClientHandler::getName() { return name; }

void ClientHandler::setName(std::string newName) {
    name = newName;
}
