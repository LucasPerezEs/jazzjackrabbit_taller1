#include "headers/monitor_clients.h"

void Monitor_clients::add_client(ClientHandler* client) {
    std::lock_guard<std::mutex> lock(m);
    list[client->getId()] = client;
}

void Monitor_clients::erase_client(int id ,Queue<Message>* setupQueue) {
    std::lock_guard<std::mutex> lock(m);
                    // 2 es para salir de la partida
    list[id]->pushState(Container(2, id, 0, 0, 0, 0, 0, AnimationType::NONE_ANIMATION, EntityType::NONE_ENTITY, 0, 0, 0));
    std::cout << "Poniendo queue de setup\n";
    list[id]->setReceiverQueue(setupQueue);
    std::cout << "Queue cambiada\n";
    list.erase(id);
}

void Monitor_clients::send(Container c) {
    std::lock_guard<std::mutex> lock(m);
    for (auto client: list) {
        client.second->pushState(c);
    }
}

int Monitor_clients::size() {
    std::lock_guard<std::mutex> lock(m);
    return list.size();
}