#ifndef SERVER_CLASS_H
#define SERVER_CLASS_H

#include <iostream>
#include <list>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include "common_protocol_desconection.h"
#include "common_socket.h"
#include "server_acceptor.h"
#include "server_broadcaster.h"
#include "server_game.h"
#include "server_protocol.h"


class Server {
private:
    Socket srv;

public:
    explicit Server(const char* servname);

    void run();


    Server(const Server&) = delete;
    Server& operator=(const Server&) = delete;
};


#endif  // SERVER_CLASS_H
