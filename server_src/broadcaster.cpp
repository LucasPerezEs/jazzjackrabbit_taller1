#include "headers/broadcaster.h"

Broadcaster::Broadcaster(std::list<ClientHandler*>& clients, Queue<Contenedor>& stateQueue):
        clients(clients), stateQueue(stateQueue) {}

void Broadcaster::run() {
    Contenedor c(0, 0, 0, 0, 0, 0, 0, AnimationType::NONE_ANIMATION, EntityType::NONE_ENTITY);

    while (_keep_running) {

        try {
            c = stateQueue.pop();
            for (auto& client: clients) {
                // std::cout << "Pusheo estados" << std::endl;
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
