#include "headers/GameBroadcasterContainer.h"

GameBroadcasterContainer::GameBroadcasterContainer(std::map<std::string, float> config,
                                                   uint32_t maxPlayers, Queue<Message>& setupQueue):
        maxPlayers(maxPlayers),
        actionQueue(),
        stateQueue(),
        broadcaster(clients, stateQueue, setupQueue),
        game(actionQueue, stateQueue, maxPlayers, std::move(config), broadcaster) {}

void GameBroadcasterContainer::addPlayer(ClientHandler* client, uint32_t character) {
    if (canAddPlayer()) {
        client->setReceiverQueue(&actionQueue);
        clients.add_client(client);
        game.addPlayer(client->getId(), character);
    }
}

bool GameBroadcasterContainer::canAddPlayer() { return (uint32_t)clients.size() < maxPlayers; }

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

int GameBroadcasterContainer::max_players() { return maxPlayers; }

int GameBroadcasterContainer::number_of_players() { return clients.size(); }
