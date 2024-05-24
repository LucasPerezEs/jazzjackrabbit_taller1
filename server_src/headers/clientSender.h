#ifndef CLIENTSENDER_H
#define CLIENTSENDER_H

#include "../../common_src/headers/desconection.h"
#include "game.h"
#include "protocol.h"
#include "../../common_src/headers/queue.h"
#include "../../common_src/headers/thread.h"
#include "../../common_src/headers/liberror.h"
#include "game.h"

class ClientSender: public Thread {
private:
    ServerProtocol& serverProtocol;
    Queue<State::StateType> queueSender;

public:
    explicit ClientSender(ServerProtocol& protocol);
    void pushState(const State::StateType& state);
    void run() override;
    void close();
};

#endif  // CLIENTSENDER_H
