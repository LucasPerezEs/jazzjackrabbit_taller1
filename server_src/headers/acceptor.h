#ifndef SERVER_ACCEPTOR_H
#define SERVER_ACCEPTOR_H

#include <list>
#include <utility>

#include <yaml-cpp/yaml.h>

#include "../../common_src/headers/liberror.h"
#include "../../common_src/headers/socket.h"
#include "../../common_src/headers/thread.h"

#include "GamesManager.h"
#include "client.h"

class Acceptor: public Thread {
private:
    Socket& sk;
    std::list<ClientHandler*>& clients;
    GamesManager& gameManager;

public:
    Acceptor(Socket& socket, std::list<ClientHandler*>& clients, GamesManager& game);
    void run() override;
    void reap_offline_clients();
    void kill_all();
    void stop() override;
};


#endif  // SERVER_ACCEPTOR_H
