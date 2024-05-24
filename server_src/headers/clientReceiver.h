#ifndef CLIENTRECEIVER_H
#define CLIENTRECEIVER_H

#include "common_protocol_desconection.h"
#include "server_protocol.h"
#include "server_queue.h"
#include "server_thread.h"

class ClientReceiver: public Thread {
private:
    ServerProtocol& serverProtocol;
    Queue<Command::ActionType>& queueReceiver;

public:
    ClientReceiver(ServerProtocol& protocol, Queue<Command::ActionType>& receiverQueue);
    void run() override;
};


#endif  // CLIENTRECEIVER_H
