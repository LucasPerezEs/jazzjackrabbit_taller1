#include "headers/clientReceiver.h"

ClientReceiver::ClientReceiver(uint32_t id,ServerProtocol& protocol, Queue<Command>& receiverQueue):
        id(id),serverProtocol(protocol), queueReceiver(receiverQueue) {}

void ClientReceiver::run() {
    while (_keep_running) {
        try {
            //recibir comando de un cliente
            auto action = serverProtocol.receive_command();
            Command command = { action, id };
            queueReceiver.push(command);
        } catch (ProtocolDesconection& d) {
            break;
        } catch (LibError& e) {
            break;
        } catch (ClosedQueue& c) {
            break;
        }
    }

    stop();
    _is_alive = false;
}
