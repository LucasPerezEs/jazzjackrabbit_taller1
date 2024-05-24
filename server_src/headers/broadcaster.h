#ifndef SERVER_BROADCASTER_H
#define SERVER_BROADCASTER_H
#include <list>

#include "client.h"
#include "game.h"
#include "../../common_src/headers/thread.h"

class Broadcaster: public Thread {
private:
    std::list<ClientHandler*>& clients;
    Queue<State::StateType>& stateQueue;


public:
    explicit Broadcaster(std::list<ClientHandler*>& clients, Queue<State::StateType>& stateQueue);
    void run() override;
    void stop() override;
};

#endif  // SERVER_BROADCASTER_H
