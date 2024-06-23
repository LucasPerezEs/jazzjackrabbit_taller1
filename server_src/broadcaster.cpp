#include "headers/broadcaster.h"


Broadcaster::Broadcaster(Monitor_clients& clients, Queue<Container>& stateQueue, Queue<Message>& setupQueue):
        clients(clients), stateQueue(stateQueue), setupQueue(setupQueue) {}

void Broadcaster::run() {
    Container c(0, 0, 0, 0, 0, 0, 0, AnimationType::NONE_ANIMATION, EntityType::NONE_ENTITY, 0, 0,
                 0, "");

    while (_keep_running) {

        try {
            c = stateQueue.pop();
            clients.send(c);
        } catch (const ClosedQueue&) {
            break;
        }
    }
    stop();
    _is_alive = false;
}

void Broadcaster::erase_client(int id) {
    clients.erase_client(id, &setupQueue);
}

void Broadcaster::stop() { _keep_running = false; }
