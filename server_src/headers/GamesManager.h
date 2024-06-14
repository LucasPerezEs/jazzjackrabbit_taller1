#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <map>
#include <vector>
#include "GameContainer.h"
#include "client.h"

class GamesManager: public Thread {
public:
    GamesManager();
    ~GamesManager();

    std::string createGame(std::string gameId, std::map<std::string, float>& config);
    bool joinGame(const std::string& gameId, ClientHandler* client);
    std::vector<std::string> listGames();
    void run();
    void stop();

private:
    void reap_offline_games();
    void kill_all_games();
    std::map<std::string, GameContainer*> games;
    std::mutex gamesMutex;
    bool _keep_running;
};

#endif  // GAMEMANAGER_H