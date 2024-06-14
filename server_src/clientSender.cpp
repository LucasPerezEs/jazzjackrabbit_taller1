#include "headers/clientSender.h"


ClientSender::ClientSender(uint32_t id,ServerProtocol& protocol): serverProtocol(protocol), id(id) {}

void ClientSender::run() {
    Contenedor init(2, id, 0, 0, 0, 0, 0, AnimationType::NONE_ANIMATION,
                    EntityType::NONE_ENTITY, 0, 0, 0);
    pushDatosObjeto(init);
    while (_keep_running) {
        try {
            Contenedor c = queueSender.pop();
            serverProtocol.send_info(c);
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
