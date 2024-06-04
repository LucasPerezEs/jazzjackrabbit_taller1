#ifndef SERVER_BROADCASTER_H
#define SERVER_BROADCASTER_H
#include <list>

#include "../../common_src/headers/thread.h"

#include "client.h"
#include "game.h"

class Broadcaster: public Thread {
private:
    std::list<ClientHandler*>& clients;
    Queue<Contenedor>& stateQueue;


public:
    explicit Broadcaster(std::list<ClientHandler*>& clients, Queue<Contenedor>& stateQueue);
    void run() override;
    void stop() override;
};

#endif  // SERVER_BROADCASTER_H
