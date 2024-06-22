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
    std::string name;
    ServerProtocol serverProtocol;
    ClientReceiver receiverThread;
    ClientSender senderThread;

    bool online;

public:
    ClientHandler(uint32_t id,Socket peer);
    void setReceiverQueue(Queue<Message>* actionQueue);
    uint32_t getId();
    std::string getName();
    void setName(std::string newName);
    bool is_online();
    void kill();
    void pushState(const Container& c);
    void go_online();
    ~ClientHandler();
};

#endif  // SERVER_CLIENT_H
