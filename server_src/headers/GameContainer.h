#ifndef GAMECONTAINER_H
#define GAMECONTAINER_H

#include <list>
#include <map>

#include "broadcaster.h"
#include "client.h"
#include "game.h"

class GameContainer {
public:
    GameContainer(std::map<std::string, float>& config, uint32_t maxPlayers);

    void addPlayer(ClientHandler* client);
    bool canAddPlayer() const;

    void start();
    void stop();
    void join();
    bool is_running();

private:
    std::list<ClientHandler*> clients;
    uint32_t maxPlayers;

    Queue<Message> actionQueue;
    Queue<Contenedor> stateQueue;

    Game game;
    Broadcaster broadcaster;
};

#endif  // GAMECONTAINER_H
