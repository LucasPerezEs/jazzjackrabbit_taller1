#include "headers/client.h"

ClientHandler::ClientHandler(uint32_t id ,Socket peer, Queue<Command>& receiverQueue):
        id(id),
        serverProtocol(std::move(peer)),
        receiverThread(id,serverProtocol, receiverQueue),
        senderThread(id,serverProtocol),
        online(true) {}

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

void ClientHandler::pushState(const Contenedor& c) { senderThread.pushDatosObjeto(c); }

ClientHandler::~ClientHandler() {}
