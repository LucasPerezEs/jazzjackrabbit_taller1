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

#include "Fuente.h"
#include "Music.h"
#include "SdlWindow.h"
#include "UIManager.h"
#include "camara.h"
#include "client.h"
#include "entity.h"
#include "event_handler.h"
#include "model_updater.h"
#include "protocol.h"

struct Tile {
    int id; // ID del tile en el tileset
    SDL_Rect srcRect; // Rectángulo de la imagen de assets
    SDL_Rect destRect; // Rectángulo de destino en la pantalla
    bool selected; // Indica si el tile está seleccionado
};

class Game {
private:
    Client& client;
    SdlWindow& window;
    std::map<int, Entity*>& entidades;
    std::map<int, Player*>& personajes;

    SDL_Texture* tilesetTexture;
    std::vector<std::vector<int>> tilemap_terreno_solido;
    UIManager& ui_manager;

    SDL_Texture* getTileTextureFromID(int id);
    std::vector<std::vector<int>> cargarCSV(const std::string& ruta);
    void SaveMapToCSV(const std::vector<Tile>& tiles, const std::string& filename);
    void draw(const std::vector<std::vector<int>>& tilemap, SDL_Texture* tilesetTexture);

    Camara* camara;


public:
    Game(Client& client, SdlWindow& window, std::map<int, Entity*>& entidades,
         std::map<int, Player*>& personajes, UIManager& ui_manager);

    void run();

    void init();
    void update();
    void render();
    void create_map();

    void close();

    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

    Game(Game&&) = default;
    Game& operator=(Game&&) = default;

    virtual ~Game() = default;
};

#endif
