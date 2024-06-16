#include "headers/GameContainer.h"

GameContainer::GameContainer(std::map<std::string, float>& config, uint32_t maxPlayers):
        maxPlayers(maxPlayers),
        actionQueue(),
        stateQueue(),
        game(actionQueue, stateQueue,maxPlayers, config),
        broadcaster(clients, stateQueue) {}

void GameContainer::addPlayer(ClientHandler* client) {
    if (canAddPlayer()) {
        client->setReceiverQueue(&actionQueue);
        clients.push_back(client);
        game.addPlayer(client->getId());
    }
}

bool GameContainer::canAddPlayer() const { return clients.size() < maxPlayers; }

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

bool GameContainer::is_running() { return game.is_running(); }