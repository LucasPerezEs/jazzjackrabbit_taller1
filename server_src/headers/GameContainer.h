#ifndef GAMECONTAINER_H
#define GAMECONTAINER_H

#include <map>
#include <list>
#include "game.h"
#include "client.h"
#include "broadcaster.h"

class GameContainer {
public:
    GameContainer(std::map<std::string, float>& config);

    void addPlayer(ClientHandler* client);

    void start();

    void stop();

    bool is_running();

private:
    Queue<Command> actionQueue;
    Queue<Contenedor> stateQueue;
    std::list<ClientHandler*> clients;
    Game game;
    Broadcaster broadcaster;
};

#endif // GAMECONTAINER_H
