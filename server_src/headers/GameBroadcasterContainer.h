#ifndef GAMEBROADCASTERCONTAINER_H
#define GAMEBROADCASTERCONTAINER_H

#include <list>
#include <map>
#include <string>

#include "broadcaster.h"
#include "client.h"
#include "game.h"

class GameBroadcasterContainer {
public:
    GameBroadcasterContainer(std::map<std::string, float> config, uint32_t maxPlayers);

    void addPlayer(ClientHandler* client, uint32_t character);
    bool canAddPlayer() const;

    void start();
    void stop();
    void join();
    bool is_running();
    int max_players();
    int number_of_players();

private:
    std::list<ClientHandler*> clients;
    uint32_t maxPlayers;

    Queue<Message> actionQueue;
    Queue<Container> stateQueue;

    Game game;
    Broadcaster broadcaster;
};

#endif  // GAMEBROADCASTERCONTAINER_H
