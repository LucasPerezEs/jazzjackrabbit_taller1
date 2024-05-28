#ifndef GAME_H
#define GAME_H

#include <string>

#include <SDL2/SDL.h>
#include <unistd.h>

#include "SdlWindow.h"
#include "client.h"
#include "event_handler.h"
#include "model_updater.h"
#include "player.h"
#include "protocol.h"

class Game {
private:
    Queue<Contenedor>& receiverQueue;
    Client& client;
    SdlWindow& window;
    Player& player;


public:
    Game(Client& client, SdlWindow& window, Player& player, Queue<Contenedor>& queue);

    void run();

    void init();
    void update(float dt);
    void render();

    void close();

    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

    Game(Game&&) = default;
    Game& operator=(Game&&) = default;

    virtual ~Game() = default;
};

#endif
