#include "headers/clientReceiver.h"

ClientReceiver::ClientReceiver(ClientProtocol& protocol, Queue<Container>& receiverQueue):
        clientProtocol(protocol), queueReceiver(receiverQueue) {}

void ClientReceiver::run() {
    while (_keep_running) {
        try {
            // recibir comando de un cliente
            Container c = clientProtocol.receive_container();
            if ((int)c.type() == 1) {
                if (c.game_container->msg_code == 2) {
                    _keep_running = false;
                }
            }
            queueReceiver.push(c);
        } catch (ProtocolDesconection& d) {
            break;
        } catch (LibError& e) {
            break;
        } catch (ClosedQueue& c) {
            break;
        }
    }
}
