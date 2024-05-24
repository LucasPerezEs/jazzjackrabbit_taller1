#include "headers/clientSender.h"

ClientSender::ClientSender(ServerProtocol& protocol): serverProtocol(protocol) {}

void ClientSender::run() {
    //State state;
    while (_keep_running) {
        try {
            //state = queueSender.pop();
            //enviar estados a todos los clientes
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

void ClientSender::close() { queueSender.close(); }

void ClientSender::pushState(const State::StateType& state) { queueSender.push(state); }
