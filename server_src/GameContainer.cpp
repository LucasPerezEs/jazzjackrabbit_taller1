#include "headers/GameContainer.h"

GameContainer::GameContainer(std::map<std::string, float>& config)
        : actionQueue(), stateQueue(), game(actionQueue, stateQueue, config), broadcaster(clients, stateQueue) {}

void GameContainer::addPlayer(ClientHandler* client) {
    client->setReceiverQueue(&actionQueue);
    clients.push_back(client);
    game.addPlayer(client->getId());
}

void GameContainer::start() {
    game.start();
    broadcaster.start();
}

void GameContainer::stop() {
    game.stop();
    broadcaster.stop();
}

void GameContainer::join() {
    game.join();
    broadcaster.join();
}

bool GameContainer::is_running(){
    return game.is_running();
}