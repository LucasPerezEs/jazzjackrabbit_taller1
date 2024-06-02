#ifndef CLIENTSENDER_H
#define CLIENTSENDER_H

#include "../../common_src/headers/desconection.h"
#include "../../common_src/headers/liberror.h"
#include "../../common_src/headers/queue.h"
#include "../../common_src/headers/thread.h"

#include "contenedor.h"
#include "game.h"
#include "protocol.h"

class ClientSender: public Thread {
private:
    ServerProtocol& serverProtocol;
    Queue<Contenedor> queueSender;

public:
    explicit ClientSender(ServerProtocol& protocol);
    void pushDatosObjeto(const Contenedor& c);
    void run() override;
    void close();
};

#endif  // CLIENTSENDER_H