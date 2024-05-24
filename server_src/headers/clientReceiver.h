#ifndef CLIENTRECEIVER_H
#define CLIENTRECEIVER_H

#include "../../common_src/headers/desconection.h"
#include "protocol.h"
#include "../../common_src/headers/queue.h"
#include "../../common_src/headers/thread.h"
#include "../../common_src/headers/liberror.h"

class ClientReceiver: public Thread {
private:
    ServerProtocol& serverProtocol;
    Queue<Command::ActionType>& queueReceiver;

public:
    ClientReceiver(ServerProtocol& protocol, Queue<Command::ActionType>& receiverQueue);
    void run() override;
};


#endif  // CLIENTRECEIVER_H
