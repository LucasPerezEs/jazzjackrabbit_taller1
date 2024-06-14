#include "headers/GameManager.h"

GameManager::GameManager() {}

std::string GameManager::createGame(std::string gameId, std::map<std::string, float>& config) {
    std::lock_guard<std::mutex> lock(gamesMutex);

    GameContainer* newGame = new GameContainer(config);
    games[gameId] = newGame;

    newGame->start();

    return gameId;
}

bool GameManager::joinGame(const std::string& gameId, ClientHandler* client) {
    std::lock_guard<std::mutex> lock(gamesMutex);
    auto it = games.find(gameId);
    if (it != games.end()) {
        it->second->addPlayer(client);
        return true;
    }
    return false;
}

std::vector<std::string> GameManager::listGames() {
    std::lock_guard<std::mutex> lock(gamesMutex);
    std::vector<std::string> gameList;
    for (const auto& game: games) {
        gameList.push_back(game.first);
    }
    return gameList;
}


void GameManager::run() {
    while (_keep_running) {
        reap_offline_games();
        std::this_thread::sleep_for(
                std::chrono::milliseconds(100));  // Simula alguna carga de trabajo
    }
}


void GameManager::reap_offline_games() {
    for (auto it = games.begin(); it != games.end();) {
        if (!it->second->is_running()) {
            it->second->stop();
            delete it->second;
            it = games.erase(it);
        } else {
            ++it;
        }
    }
}

void GameManager::kill_all_games() {
    for (auto& gamePair: games) {
        gamePair.second->stop();
        delete gamePair.second;
    }
    games.clear();
}

void GameManager::stop() {
    _keep_running = false;
    kill_all_games();
}

GameManager::~GameManager() {
    stop();
    std::lock_guard<std::mutex> lock(gamesMutex);
    for (auto& gamePair: games) {
        delete gamePair.second;
    }
    games.clear();
}
