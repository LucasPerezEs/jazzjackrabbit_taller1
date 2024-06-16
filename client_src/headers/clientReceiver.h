#ifndef CLIENTRECEIVER_H
#define CLIENTRECEIVER_H

#include "../../common_src/headers/desconection.h"
#include "../../common_src/headers/liberror.h"
#include "../../common_src/headers/queue.h"
#include "../../common_src/headers/thread.h"
#include "../../server_src/headers/contenedor.h"

#include "protocol.h"

class ClientReceiver: public Thread {
private:
    ClientProtocol& clientProtocol;
    Queue<Container>& queueReceiver;

public:
    ClientReceiver(ClientProtocol& protocol, Queue<Container>& receiverQueue);
    void run() override;
};


#endif  // CLIENTRECEIVER_H
