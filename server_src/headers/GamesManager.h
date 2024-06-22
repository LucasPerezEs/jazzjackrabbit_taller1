#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <map>
#include <string>
#include <vector>

#include <yaml-cpp/yaml.h>

#include "../../common_src/headers/Message.h"
#include "../../common_src/headers/cheat_commands.h"

#include "GameBroadcasterContainer.h"
#include "client.h"

class GamesManager: public Thread {
public:
    GamesManager();
    ~GamesManager();

    void addClient(uint32_t clientId, ClientHandler* client);

    bool createGame(std::string gameId, uint32_t maxPlayers, std::vector<uint32_t> cheats);
    bool joinGame(const std::string& gameId, ClientHandler* client, uint32_t character);
    bool listGames(std::vector<std::string>& gameList);
    bool savedMap(std::string& mapName, std::vector<std::vector<std::string>>& mapReceived);
    bool createMap(std::string& mapName, std::vector<std::vector<std::string>>& mapReceived);
    virtual void run() override;
    virtual void stop() override;

private:
    std::mutex gamesMutex;

    Queue<Message> setupQueue;
    Queue<Container> stateQueue;

    std::map<std::string, GameBroadcasterContainer*> games;
    std::map<uint32_t, ClientHandler*> clients;

    void activate_cheats(const std::vector<uint32_t>& cheats, std::map<std::string, float>& config);
    void reap_offline_games();
    void kill_all_games();
};

#endif  // GAMEMANAGER_H
