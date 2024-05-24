#ifndef SERVER_CLIENT_H
#define SERVER_CLIENT_H

#include <utility>

#include <arpa/inet.h>

#include "clientReceiver.h"
#include "clientSender.h"
#include "../../common_src/headers/socket.h"
#include "game.h"
#include "../../common_src/headers/protocol.h"
#include "../../common_src/headers/thread.h"


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
    void pushState(const State::StateType state);
    void go_online();
    ~ClientHandler();
};

#endif  // SERVER_CLIENT_H
