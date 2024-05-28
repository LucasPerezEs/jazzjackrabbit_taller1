#include "headers/clientSender.h"


ClientSender::ClientSender(ServerProtocol& protocol): serverProtocol(protocol) {}

void ClientSender::run() {
    Contenedor c(0, 0, 0, 0, 0, false);
    while (_keep_running) {
        try {
            c = queueSender.pop();
            serverProtocol.send_datos_objeto(c);
            // enviar estados a todos los clientes
        } catch (ProtocolDesconection& d) {
            break;
        } catch (LibError& e) {
            break;
        } catch (ClosedQueue& q) {
            break;
        }
    }
    stop();
    _is_alive = false;
}

void ClientSender::close() { queueSender.close(); }

void ClientSender::pushDatosObjeto(const Contenedor& c) { queueSender.push(c); }
