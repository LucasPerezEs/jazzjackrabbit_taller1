#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <yaml-cpp/yaml.h>
#include <map>
#include <vector>
#include "GameContainer.h"
#include "client.h"

class GamesManager: public Thread {
public:
    GamesManager();
    ~GamesManager();

    void addClient(uint32_t clientId, ClientHandler* client);

    std::string createGame(std::string gameId, std::map<std::string, float>& config);
    bool joinGame(const std::string& gameId, ClientHandler* client);
    std::vector<std::string> listGames();
    void run();
    void stop();

private:
    std::mutex gamesMutex;

    Queue<Command> setupQueue;
    Queue<Contenedor> stateQueue;

    std::map<std::string, GameContainer*> games;
    std::map<uint32_t, ClientHandler*> clients;

    void reap_offline_games();
    void kill_all_games();

};

#endif  // GAMEMANAGER_H
