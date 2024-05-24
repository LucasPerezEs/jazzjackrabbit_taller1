#ifndef SERVER_ACCEPTOR_H
#define SERVER_ACCEPTOR_H

#include <list>
#include <utility>

#include "common_socket.h"
#include "server_client.h"
#include "server_game.h"
#include "server_thread.h"

class Acceptor: public Thread {
private:
    Socket& sk;
    std::list<ClientHandler*>& clients;

    Queue<Command::ActionType>& actionQueue;


public:
    Acceptor(Socket& socket, std::list<ClientHandler*>& clients,
             Queue<Command::ActionType>& actionQueue);
    void run() override;
    void reap_offline_clients();
    void kill_all();
    void stop() override;
};


#endif  // SERVER_ACCEPTOR_H
