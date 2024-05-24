#include "server_clientSender.h"

#include "common_liberror.h"
#include "server_game.h"

ClientSender::ClientSender(ServerProtocol& protocol): serverProtocol(protocol) {}

void ClientSender::run() {
    EnemyEvent event;
    while (_keep_running) {
        try {
            event = queueSender.pop();
            serverProtocol.send_event(event.enemies_alive_cnt, event.enemies_dead_cnt,
                                      event.event_type);
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

void ClientSender::pushEvent(const EnemyEvent& event) { queueSender.push(event); }
