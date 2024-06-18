#include "headers/GameBroadcasterContainer.h"

GameBroadcasterContainer::GameBroadcasterContainer(std::map<std::string, float>& config, uint32_t maxPlayers):
        maxPlayers(maxPlayers),
        actionQueue(),
        stateQueue(),
        game(actionQueue, stateQueue,maxPlayers, config),
        broadcaster(clients, stateQueue) {}

void GameBroadcasterContainer::addPlayer(ClientHandler* client, uint32_t character) {
    if (canAddPlayer()) {
        client->setReceiverQueue(&actionQueue);
        clients.push_back(client);
        game.addPlayer(client->getId(), character);
    }
}

bool GameBroadcasterContainer::canAddPlayer() const { return clients.size() < maxPlayers; }

void GameBroadcasterContainer::start() {
    game.start();
    broadcaster.start();
}

void GameBroadcasterContainer::stop() {
    game.stop();
    broadcaster.stop();
}

void GameBroadcasterContainer::join() {
    game.join();
    broadcaster.join();
}

bool GameBroadcasterContainer::is_running() { return game.is_running(); }

int GameBroadcasterContainer::max_players() {
    return maxPlayers;
}

int GameBroadcasterContainer::number_of_players() {
    return clients.size();
}
