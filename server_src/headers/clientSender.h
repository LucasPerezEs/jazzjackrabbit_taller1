#ifndef CLIENTSENDER_H
#define CLIENTSENDER_H

#include "../../common_src/headers/desconection.h"
#include "../../common_src/headers/liberror.h"
#include "../../common_src/headers/queue.h"
#include "../../common_src/headers/thread.h"


#include "game.h"
#include "protocol.h"

class ClientSender: public Thread {
private:

    ServerProtocol& serverProtocol;
    uint32_t id;
    Queue<Container> queueSender;

public:
    explicit ClientSender(uint32_t id,ServerProtocol& protocol);
    void pushDatosObjeto(const Container& c);
    void run() override;
    void close();
};

#endif  // CLIENTSENDER_H
