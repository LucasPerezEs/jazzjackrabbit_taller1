#include "headers/clientReceiver.h"

// cppcheck-suppress uninitMemberVar
ClientReceiver::ClientReceiver(uint32_t id, ServerProtocol& protocol):
        id(id), serverProtocol(protocol) {}

void ClientReceiver::run() {
    while (_keep_running) {
        try {
            Message msg = serverProtocol.receive_message();
            if ((int)msg.type() == 1) {
                std::cout << "Recibiendo mensaje de setup en el receiver\n";
            }
            msg.setId(id);
            if ((int)msg.type() == 1) {
                std::cout << "Seteando id al mensaje\n";
            }
            queueReceiver->push(msg);
            if ((int)msg.type() == 1) {
                std::cout << "Pusheado a la cola y saliendo\n";
            }
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


void ClientReceiver::setQueue(Queue<Message>* queue) {
    queueReceiver = queue;
}
