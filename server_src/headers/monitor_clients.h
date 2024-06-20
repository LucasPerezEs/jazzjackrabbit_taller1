#ifndef MONITOR_CLIENTS_H_
#define MONITOR_CLIENTS_H_

#include <mutex>

#include "client.h"

class Monitor_clients {
    private:
    std::mutex m;
    std::map<int, ClientHandler*> list;

    public:
    void add_client(ClientHandler* client);
    void erase_client(int id, Queue<Message>* setupQueue);
    void send(Container c);
    int size();
};

#endif
