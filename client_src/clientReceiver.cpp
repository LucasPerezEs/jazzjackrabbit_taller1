#include "headers/clientReceiver.h"

ClientReceiver::ClientReceiver(ClientProtocol& protocol, Queue<Container>& receiverQueue):
        clientProtocol(protocol), queueReceiver(receiverQueue) {}

void ClientReceiver::run() {
    std::cout << "Entrando al loop del receiver\n";
    while (_keep_running) {
        std::cout << "Estoy en el loop del receiver\n";
        try {
            // recibir comando de un cliente
            Container c = clientProtocol.receive_container();
            std::cout << "Tipo de container: " << (int)c.type() << "\n";
            if ((int)c.type() == 1) {
                if (c.game_container->msg_code == 2) {
                    _keep_running = false;
                }
                queueReceiver.push(c);
            }
        } catch (ProtocolDesconection& d) {
            break;
        } catch (LibError& e) {
            break;
        } catch (ClosedQueue& c) {
            break;
        }
    }
    std::cout << "Saliendo del receiver\n";
}
