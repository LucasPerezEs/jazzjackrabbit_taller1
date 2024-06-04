#ifndef GAME_H
#define GAME_H

#include <cmath>
#include <fstream>
#include <map>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include <SDL2/SDL.h>
#include <unistd.h>

#include "SdlWindow.h"
#include "client.h"
#include "entity.h"
#include "event_handler.h"
#include "model_updater.h"
#include "protocol.h"

class Game {
private:
    Client& client;
    SdlWindow& window;
    std::map<int, Entity*>& entidades;

    SDL_Texture* tilesetTexture;
    std::vector<std::vector<int>> tilemap_terreno_solido;

    std::vector<std::vector<int>> cargarCSV(const std::string& ruta);
    void draw(const std::vector<std::vector<int>>& tilemap, SDL_Texture* tilesetTexture);


public:
    Game(Client& client, SdlWindow& window, std::map<int, Entity*>& entidades);

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
