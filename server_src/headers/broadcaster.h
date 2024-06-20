#ifndef SERVER_BROADCASTER_H
#define SERVER_BROADCASTER_H
#include <list>

#include "../../common_src/headers/thread.h"

#include "monitor_clients.h"
#include "client.h"
#include "game.h"

class Broadcaster: public Thread {
private:
    Monitor_clients& clients;
    Queue<Container>& stateQueue;
    Queue<Message>& setupQueue;


public:
    explicit Broadcaster(Monitor_clients& clients, Queue<Container>& stateQueue, Queue<Message>& setupQueue);
    void run() override;
    void stop() override;
    void erase_client(int id);
};

#endif  // SERVER_BROADCASTER_H
