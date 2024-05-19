#ifndef GAME_H
#define GAME_H

#include <string>

#include <SDL2/SDL.h>
#include <unistd.h>

#include "SdlWindow.h"
#include "event_handler.h"
#include "model_updater.h"
#include "player.h"
#include "protocol.h"

class Game {
private:
    ClientProtocol protocol;
    EventHandler event_handler;
    // Player& player;
    SdlWindow& window;
    ModelUpdater updater;

public:
    Game(const std::string& hostname, const std::string& servname, SdlWindow& window);

    void run();

    void init();

    void render();

    void close();

    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

    Game(Game&&) = default;
    Game& operator=(Game&&) = default;

    virtual ~Game() = default;
};

#endif
