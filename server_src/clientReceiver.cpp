#include "headers/clientReceiver.h"

// cppcheck-suppress uninitMemberVar
ClientReceiver::ClientReceiver(uint32_t id, ServerProtocol& protocol):
        id(id), serverProtocol(protocol) {}

void ClientReceiver::run() {
    while (_keep_running) {
        try {
            auto action = serverProtocol.receive_command();
            Command command = {action, id};
            queueReceiver->push(command);

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


void ClientReceiver::setQueue(Queue<Command>* queue) { queueReceiver = queue; }
