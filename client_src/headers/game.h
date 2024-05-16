#ifndef GAME_H
#define GAME_H

#include <string>

#include <SDL2/SDL.h>
#include <unistd.h>

#include "SdlWindow.h"
#include "controlador_cliente.h"
#include "player.h"

#define FRAME_RATE 1000000.0f / 40.0f

class Game {
private:
    ControladorCliente controlador_cliente;
    Player& player;
    SdlWindow& window;

public:
    Game(const std::string& hostname, const std::string& servname, Player& player,
         SdlWindow& window);

    void run();

    void update(float dt);

    void init();

    void render();

    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

    Game(Game&&) = default;
    Game& operator=(Game&&) = default;

    virtual ~Game() = default;
};

#endif
