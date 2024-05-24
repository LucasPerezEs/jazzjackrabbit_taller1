#include "headers/broadcaster.h"

Broadcaster::Broadcaster(std::list<ClientHandler*>& clients, Queue<State::StateType>& stateQueue):
        clients(clients), stateQueue(stateQueue) {}

void Broadcaster::run() {
    State::StateType state;

    while (_keep_running) {

        try {
            state = stateQueue.pop();
            for (auto& client: clients) {
                std::cout << "Pusheo estados" << std::endl;
                client->pushState(state);
            }
        } catch (const ClosedQueue&) {
            break;
        }
    }
    stop();
    _is_alive = false;
}

void Broadcaster::stop() { _keep_running = false; }
