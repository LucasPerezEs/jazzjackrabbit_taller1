#ifndef SERVER_CLIENT_H
#define SERVER_CLIENT_H

#include <utility>

#include <arpa/inet.h>

#include "../../common_src/headers/protocol.h"
#include "../../common_src/headers/socket.h"
#include "../../common_src/headers/thread.h"

#include "clientReceiver.h"
#include "clientSender.h"
#include "game.h"

// AGREGA ID JUGADOR
class ClientHandler {
private:
    uint32_t id;
    ServerProtocol serverProtocol;
    ClientReceiver receiverThread;
    ClientSender senderThread;

    bool online;

public:
    ClientHandler(uint32_t id,Socket peer, Queue<Command>& receiverQueue);
    uint32_t getId();
    bool is_online();
    void kill();
    void pushState(const Contenedor& c);
    void go_online();
    ~ClientHandler();
};

#endif  // SERVER_CLIENT_H
