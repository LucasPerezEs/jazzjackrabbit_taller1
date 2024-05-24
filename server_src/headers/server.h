#ifndef SERVER_CLASS_H
#define SERVER_CLASS_H

#include <iostream>
#include <list>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include "../../common_src/headers/desconection.h"
#include "../../common_src/headers/socket.h"
#include "acceptor.h"
#include "broadcaster.h"
#include "game.h"
#include "../../common_src/headers/protocol.h"


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
