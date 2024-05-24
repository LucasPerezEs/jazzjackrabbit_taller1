#ifndef SERVER_BROADCASTER_H
#define SERVER_BROADCASTER_H
#include <list>

#include "client.h"
#include "server_game.h"
#include "server_thread.h"

class Broadcaster: public Thread {
private:
    std::list<ClientHandler*>& clients;
    Queue<EnemyEvent>& eventQueue;


public:
    explicit Broadcaster(std::list<ClientHandler*>& clients, Queue<EnemyEvent>& eventQueue);
    void run() override;
    void stop() override;
};

#endif  // SERVER_BROADCASTER_H
