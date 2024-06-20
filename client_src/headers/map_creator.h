#ifndef MAPCREATOR_H
#define MAPCREATOR_H

#include <cmath>
#include <fstream>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

#include <SDL2/SDL.h>
#include "client.h"
#include "drawer.h"
#include "SdlWindow.h"

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


class MapCreator {
private:
    Client& client;
    SdlWindow window;
    std::map<std::tuple<int, int>, Tile> mapTiles;

    void SaveMapToCSV(std::ofstream& file, bool& is_already_create);
    void save_values(Tile& selectedTile, int& width_texture, int& window_width, int& window_height,
                     SDL_Event& event);

public:
    explicit MapCreator(Client& client);

    void select_map();
    void create_map(std::ofstream& file, bool& is_already_create);
    void modify_map(std::ofstream& file, bool& is_already_create);
    std::vector<std::vector<int>> cargarCSV(const std::string& ruta);

    MapCreator(const MapCreator&) = delete;
    MapCreator& operator=(const MapCreator&) = delete;

    MapCreator(MapCreator&&) = default;
    MapCreator& operator=(MapCreator&&) = default;

    ~MapCreator() = default;
};

#endif
