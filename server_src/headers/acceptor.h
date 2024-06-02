#ifndef SERVER_ACCEPTOR_H
#define SERVER_ACCEPTOR_H

#include <list>
#include <utility>

#include "../../common_src/headers/socket.h"
#include "client.h"
#include "game.h"
#include "../../common_src/headers/thread.h"
#include "../../common_src/headers/liberror.h"

class Acceptor: public Thread {
private:
    Socket& sk;
    std::list<ClientHandler*>& clients;


    Queue<Command>& actionQueue;
    Game& game;


public:
    Acceptor(Socket& socket, std::list<ClientHandler*>& clients,
             Queue<Command>& actionQueue, Game& game);
    void run() override;
    void reap_offline_clients();
    void kill_all();
    void stop() override;
};


#endif  // SERVER_ACCEPTOR_H
