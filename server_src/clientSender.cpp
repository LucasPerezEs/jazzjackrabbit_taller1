#include "headers/clientSender.h"


ClientSender::ClientSender(uint32_t id, ServerProtocol& protocol):
        serverProtocol(protocol), id(id) {}

void ClientSender::run() {
    while (_keep_running) {
        try {
            Container c = queueSender.pop();
            serverProtocol.send_container(c);
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

void ClientSender::pushDatosObjeto(const Container& c) { queueSender.push(c); }
