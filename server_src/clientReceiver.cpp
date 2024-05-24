#include "server_clientReceiver.h"

#include "common_liberror.h"

ClientReceiver::ClientReceiver(ServerProtocol& protocol, Queue<Command::ActionType>& receiverQueue):
        serverProtocol(protocol), queueReceiver(receiverQueue) {}

void ClientReceiver::run() {
    while (_keep_running) {
        try {
            Command::ActionType command = serverProtocol.receive_command();
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
