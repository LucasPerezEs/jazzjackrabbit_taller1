#include "headers/clientReceiver.h"

ClientReceiver::ClientReceiver(ClientProtocol& protocol, Queue<Container>& receiverQueue):
        clientProtocol(protocol), queueReceiver(receiverQueue) {}

void ClientReceiver::run() {
    while (_keep_running) {
        try {
            // recibir comando de un cliente
            Container c = clientProtocol.receive_container();
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
