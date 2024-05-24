#ifndef CLIENTSENDER_H
#define CLIENTSENDER_H

#include "common_protocol_desconection.h"
#include "server_game.h"
#include "server_protocol.h"
#include "server_queue.h"
#include "server_thread.h"

class ClientSender: public Thread {
private:
    ServerProtocol& serverProtocol;
    Queue<EnemyEvent> queueSender;

public:
    explicit ClientSender(ServerProtocol& protocol);
    void pushEvent(const EnemyEvent& event);
    void run() override;
    void close();
};

#endif  // CLIENTSENDER_H
