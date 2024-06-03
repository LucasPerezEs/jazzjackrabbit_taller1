#ifndef CLIENTRECEIVER_H
#define CLIENTRECEIVER_H

#include "../../common_src/headers/desconection.h"
#include "protocol.h"
#include "../../common_src/headers/queue.h"
#include "../../common_src/headers/thread.h"
#include "../../common_src/headers/liberror.h"

class ClientReceiver: public Thread {
private:
    uint32_t id;
    ServerProtocol& serverProtocol;
    Queue<Command>& queueReceiver;

public:
    ClientReceiver(uint32_t id, ServerProtocol& protocol, Queue<Command>& receiverQueue);
    void run() override;
};


#endif  // CLIENTRECEIVER_H
