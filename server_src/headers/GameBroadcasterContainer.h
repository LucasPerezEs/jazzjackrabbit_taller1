#ifndef GAMEBROADCASTERCONTAINER_H
#define GAMEBROADCASTERCONTAINER_H

#include <list>
#include <map>
#include <string>

#include "broadcaster.h"
#include "client.h"
#include "game.h"
#include "monitor_clients.h"


class GameBroadcasterContainer {
public:
    GameBroadcasterContainer(std::map<std::string, float> config, uint32_t maxPlayers, const std::string& mapName,
                             Queue<Message>& setupQueue);

    void addPlayer(ClientHandler* client, uint32_t character);
    bool canAddPlayer();
    void getMapName(std::string& mapName);

    void start();
    void stop();
    void join();
    bool is_running();
    bool game_started();
    int max_players();
    int number_of_players();

private:
    Monitor_clients clients;
    uint32_t maxPlayers;

    Queue<Message> actionQueue;
    Queue<Container> stateQueue;

    Broadcaster broadcaster;
    bool gameStarted;
    bool gameEnded;
    Game game;
};

#endif  // GAMEBROADCASTERCONTAINER_H
