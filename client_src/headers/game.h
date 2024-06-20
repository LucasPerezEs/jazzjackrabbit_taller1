#ifndef GAME_H
#define GAME_H

#include <cmath>
#include <fstream>
#include <map>
#include <sstream>
#include <string>
#include <tuple>
#include <unordered_map>
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

#define ITEM 0
#define SOLIDO 1
#define DECORACION 2

#define TILE_MAP_ASSETS 16  // Tamaño en el que se ve el asset al crear.
#define TILE_MAP_CREATED 8  // Tamaño en el que se ve el mapa al crearlo.

struct Tile {
    // cppcheck-suppress unusedStructMember
    int id;  // ID del tile en el tileset
    // cppcheck-suppress unusedStructMember
    int type;  // Si es tipo SOLIDO-DECORACION-ITEM
    SDL_Rect srcRect;
    SDL_Rect destRect;
    // cppcheck-suppress unusedStructMember
    bool selected;  // Indica si el tile está seleccionado
};


class Game {
private:
    Queue<Container> receiverQueue;
    Client& client;
    SdlWindow window;
    std::map<int, Entity*> entidades;
    std::map<int, Player*> personajes;
    std::map<std::tuple<int, int>, Tile> mapTiles;

    SDL_Texture* tilesetTexture;
    std::vector<std::vector<int>> tilemap_terreno_solido;
    UIManager ui_manager;

    ClientReceiver client_receiver;
    bool in_menu;
    SoundManager sound_manager;
    EventHandler event_handler;  // eventos teclado (sender)
    ModelUpdater updater;        // actualizar modelos (receiver)

    std::vector<std::vector<int>> cargarCSV(const std::string& ruta);
    void SaveMapToCSV(const std::string& filename);
    void draw(const std::vector<std::vector<int>>& tilemap, SDL_Texture* tilesetTexture);
    void save_values(Tile& selectedTile, int& width_texture, int& window_width, int& window_height,
                     SDL_Event& event);

    Camara* camara;


public:
    explicit Game(Client& client);

    void run();

    void init();
    void update();
    void render();
    void create_map();

    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

    Game(Game&&) = default;
    Game& operator=(Game&&) = default;

    ~Game();
};

#endif
