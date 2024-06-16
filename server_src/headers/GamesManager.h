#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <map>
#include <vector>

#include <yaml-cpp/yaml.h>

#include "../../common_src/headers/Message.h"

#include "GameBroadcasterContainer.h"
#include "client.h"

class GamesManager: public Thread {
public:
    GamesManager();
    ~GamesManager();

    void addClient(uint32_t clientId, ClientHandler* client);

    std::string createGame(std::string gameId, uint32_t maxPlayers,
                           std::map<std::string, float>& config);
    bool joinGame(const std::string& gameId, ClientHandler* client);
    std::vector<std::string> listGames();
    void run();
    void stop();

private:
    std::mutex gamesMutex;

    Queue<Message> setupQueue;
    Queue<Contenedor> stateQueue;

    std::map<std::string, GameBroadcasterContainer*> games;
    std::map<uint32_t, ClientHandler*> clients;

    void reap_offline_games();
    void kill_all_games();
};

#endif  // GAMEMANAGER_H
