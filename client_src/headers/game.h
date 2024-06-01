#ifndef GAME_H
#define GAME_H

#include <map>
#include <string>

#include <SDL2/SDL.h>
#include <unistd.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>

#include "SdlWindow.h"
#include "client.h"
#include "entity.h"
#include "event_handler.h"
#include "model_updater.h"
#include "player.h"
#include "protocol.h"

class Game {
private:
    Client& client;
    SdlWindow& window;
    Player& player;
    std::map<int, Entity*>& entidades;

    std::vector<std::vector<int>> cargarCSV(const std::string& ruta);
    void draw(std::vector<std::vector<int>>& tilemap, SDL_Texture* tilesetTexture);


public:
    Game(Client& client, SdlWindow& window, Player& player, std::map<int, Entity*>& entidades);

    void run();

    void init();
    void update();
    void render();

    void close();

    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

    Game(Game&&) = default;
    Game& operator=(Game&&) = default;

    virtual ~Game() = default;
};

#endif
