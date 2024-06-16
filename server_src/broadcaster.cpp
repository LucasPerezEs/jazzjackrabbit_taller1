#include "headers/broadcaster.h"

Broadcaster::Broadcaster(std::list<ClientHandler*>& clients, Queue<Container>& stateQueue):
        clients(clients), stateQueue(stateQueue) {}

void Broadcaster::run() {
    Container c(0, 0, 0, 0, 0, 0, 0, AnimationType::NONE_ANIMATION, EntityType::NONE_ENTITY, 0, 0,
                 0);

    while (_keep_running) {

        try {
            c = stateQueue.pop();
            for (auto& client: clients) {
                client->pushState(c);
            }
        } catch (const ClosedQueue&) {
            break;
        }
    }
    stop();
    _is_alive = false;
}

void Broadcaster::stop() { _keep_running = false; }
