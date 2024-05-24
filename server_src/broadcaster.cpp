#include "server_broadcaster.h"

Broadcaster::Broadcaster(std::list<ClientHandler*>& clients, Queue<EnemyEvent>& eventQueue):
        clients(clients), eventQueue(eventQueue) {}

void Broadcaster::run() {
    EnemyEvent event;

    while (_keep_running) {

        try {
            event = eventQueue.pop();
            for (auto& client: clients) {
                client->pushEvent(event);
            }
        } catch (const ClosedQueue&) {
            break;
        }
    }
    stop();
    _is_alive = false;
}

void Broadcaster::stop() { _keep_running = false; }
