#include "headers/clientReceiver.h"

ClientReceiver::ClientReceiver(ClientProtocol& protocol, Queue<Contenedor>& receiverQueue):
        clientProtocol(protocol), queueReceiver(receiverQueue) {}

void ClientReceiver::run() {
    while (_keep_running) {
        try {
            // recibir comando de un cliente
            Contenedor c = clientProtocol.receive_info();
            queueReceiver.push(c);
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
