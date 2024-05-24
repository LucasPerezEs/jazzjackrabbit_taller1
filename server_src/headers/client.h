#ifndef SERVER_CLIENT_H
#define SERVER_CLIENT_H

#include <utility>

#include <arpa/inet.h>

#include "clientReceiver.h"
#include "clientSender.h"
#include "common_socket.h"
#include "server_game.h"
#include "server_protocol.h"
#include "server_thread.h"


class ClientHandler {
private:
    ServerProtocol serverProtocol;

    ClientReceiver receiverThread;
    ClientSender senderThread;

    bool online;

public:
    ClientHandler(Socket peer, Queue<Command::ActionType>& receiverQueue);
    bool is_online();
    void kill();
    void pushEvent(const EnemyEvent event);
    void go_online();
    ~ClientHandler();
};

#endif  // SERVER_CLIENT_H
