#ifndef MAPCREATOR_H
#define MAPCREATOR_H

#include <cmath>
#include <map>
#include <fstream>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>
#include <iostream>

#include <SDL2/SDL.h>
#include "client.h"
#include "drawer.h"
#include "tile.h"
#include "SdlWindow.h"

#define TILE_MAP_ASSETS 16  // Tamaño en el que se ve el asset al crear.
#define TILE_MAP_CREATED 8  // Tamaño en el que se ve el mapa al crearlo.

class MapCreator {
private:
    Client& client;
    SdlWindow window;
    std::map<std::tuple<int, int>, Tile> mapTiles;

    void saveMapToCSV(std::string& filename, bool& is_already_create);
    void save_values(Tile& selectedTile, const double& minX, const double& maxX, const double& minY, const double& maxY,
                     SDL_Event& event);

public:
    explicit MapCreator(Client& client);

    void select_map();
    void create_map(std::string& filename, bool& is_already_create);
    void modify_map(std::string& filename, bool& is_already_create);

    std::map<std::tuple<int, int>, Tile> loadCSV(const std::string&filename);
    std::vector<std::vector<int>> cargarCSV(const std::string& ruta);

    MapCreator(const MapCreator&) = delete;
    MapCreator& operator=(const MapCreator&) = delete;

    MapCreator(MapCreator&&) = default;
    MapCreator& operator=(MapCreator&&) = default;

    ~MapCreator() = default;
};

#endif
