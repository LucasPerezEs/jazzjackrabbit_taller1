#include "headers/GamesManager.h"

GamesManager::GamesManager(): setupQueue(), stateQueue() {}

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

    Command command;

    while (_keep_running) {
        command = setupQueue.pop();
        uint32_t clientId = command.clientId;
        switch (command.action) {
            case Command::JOIN_GAME:
                std::cout << "case Command::JOIN_GAME:" << std::endl;
                joinGame("PruebaManager", clients[clientId]);
                // Asignar el gameId en el caso JOIN_GAME
                // gameId = command.gameId;
                //joinGame("Prueba", clients[clientId]);
                // push join
                break;
            case Command::CREATE_GAME:
                std::cout << "case Command::CREATE_GAME:" << std::endl;
                // gameId = command.gameId;
                //createGame("Prueba", config);
                // push create
                break;
            case Command::GET_GAME_LIST:
                std::cout << "case Command::GET_GAME_LIST:" << std::endl;
                //std::cout << "case Command::JOIN_GAME:" << std::endl;
                listGames();
                // push gameList
                break;
            default:
                std::cout << "Comando desconocido" << std::endl;
                break;
        }
        reap_offline_games();
    }
    stop();
    _is_alive = false;
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

void GamesManager::addClient(uint32_t clientId, ClientHandler* client) {
    std::lock_guard<std::mutex> lock(gamesMutex);
    clients[clientId] = client;
    client->setReceiverQueue(&setupQueue);
}