#include "headers/clientReceiver.h"

// cppcheck-suppress uninitMemberVar
ClientReceiver::ClientReceiver(uint32_t id, ServerProtocol& protocol):
        id(id), serverProtocol(protocol) {}

void ClientReceiver::run() {
    while (_keep_running) {
        try {
            Message msg = serverProtocol.receive_message();
            msg.setId(id);
            queueReceiver->push(msg);
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
