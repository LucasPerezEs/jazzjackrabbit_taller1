#include "headers/GamesManager.h"

GamesManager::GamesManager() {}

std::string GamesManager::createGame(std::string gameId, std::map<std::string, float>& config) {
    std::lock_guard<std::mutex> lock(gamesMutex);

    GameContainer* newGame = new GameContainer(config);
    games[gameId] = newGame;

    newGame->start();

    return gameId;
}

bool GamesManager::joinGame(const std::string& gameId, ClientHandler* client) {
    std::lock_guard<std::mutex> lock(gamesMutex);
    auto it = games.find(gameId);
    if (it != games.end()) {
        it->second->addPlayer(client);
        return true;
    }
    return false;
}

std::vector<std::string> GamesManager::listGames() {
    std::lock_guard<std::mutex> lock(gamesMutex);
    std::vector<std::string> gameList;
    for (const auto& game: games) {
        gameList.push_back(game.first);
    }
    return gameList;
}


void GamesManager::run() {
    while (_keep_running) {
        reap_offline_games();
        std::this_thread::sleep_for(
                std::chrono::milliseconds(100));  // Simula alguna carga de trabajo
    }
}


void GamesManager::reap_offline_games() {
    for (auto it = games.begin(); it != games.end();) {
        if (!it->second->is_running()) {
            it->second->stop();
            it->second->join();
            delete it->second;
            it = games.erase(it);
        } else {
            ++it;
        }
    }
}

void GamesManager::kill_all_games() {
    for (auto& gamePair: games) {
        gamePair.second->stop();
        gamePair.second->join();
        delete gamePair.second;
    }
    games.clear();
}

void GamesManager::stop() {
    _keep_running = false;
    kill_all_games();
}


GamesManager::~GamesManager() {
    std::lock_guard<std::mutex> lock(gamesMutex);
    for (auto& gamePair: games) {
        delete gamePair.second;
    }
    games.clear();
}
