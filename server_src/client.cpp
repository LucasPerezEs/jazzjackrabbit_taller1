#include "server_client.h"

ClientHandler::ClientHandler(Socket peer, Queue<Command::ActionType>& receiverQueue):
        serverProtocol(std::move(peer)),
        receiverThread(serverProtocol, receiverQueue),
        senderThread(serverProtocol),
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

void ClientHandler::pushEvent(const EnemyEvent event) { senderThread.pushEvent(event); }

ClientHandler::~ClientHandler() {}
