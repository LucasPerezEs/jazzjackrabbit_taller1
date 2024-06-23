#include "headers/GameBroadcasterContainer.h"

GameBroadcasterContainer::GameBroadcasterContainer(std::map<std::string, float> config,
                                                   uint32_t maxPlayers, Queue<Message>& setupQueue):
        maxPlayers(maxPlayers),
        actionQueue(),
        stateQueue(),
        broadcaster(clients, stateQueue, setupQueue),
        gameStarted(false),
        gameEnded(false),
        game(actionQueue, stateQueue, maxPlayers, std::move(config), broadcaster, gameStarted, gameEnded) {}

void GameBroadcasterContainer::addPlayer(ClientHandler* client, uint32_t character) {
    if (canAddPlayer()) {
        client->setReceiverQueue(&actionQueue);
        clients.add_client(client);
        game.addPlayer(client->getId(), character, client->getName());
        if (number_of_players() == max_players()) {
            gameStarted = true;
            start();
        }
    }
}

bool GameBroadcasterContainer::canAddPlayer() { return (uint32_t)clients.size() < maxPlayers; }

void GameBroadcasterContainer::start() {
    game.start();
    broadcaster.start();
}

void GameBroadcasterContainer::stop() {
    if (gameStarted) {
        game.stop();
        broadcaster.stop();
    }
}

void GameBroadcasterContainer::join() {
    if (gameStarted) {
        game.join();
        broadcaster.join();
    }
}

bool GameBroadcasterContainer::is_running() {
    if (gameEnded) {
        return false;
    }
    if (gameStarted) {
        return game.is_running();
    }
    return true;
}


bool GameBroadcasterContainer::game_started() {
    return gameStarted;
}

int GameBroadcasterContainer::max_players() { return maxPlayers; }

int GameBroadcasterContainer::number_of_players() { return clients.size(); }
