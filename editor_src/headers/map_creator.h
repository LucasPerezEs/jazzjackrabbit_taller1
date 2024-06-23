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
#include <SDL2/SDL_image.h>

#include "tile.h"
#include "SdlWindow.h"

#define TILE_MAP_ASSETS 16  // Tamaño en el que se ve el asset al crear.
#define TILE_MAP_CREATED 8  // Tamaño en el que se ve el mapa al crearlo.

class MapCreator {
    std::string mapName;
    double mapWidth;
    double mapHeight;
    SdlWindow window;
    bool is_already_create;
    std::string path_maps = "../server_src/maps/";
    std::map<std::tuple<int, int>, Tile> mapTiles;
    std::map<std::tuple<int, int>, Tile> mapSpawn;

    std::map<std::tuple<int, int>, Tile> loadEmptyCSV();
    std::map<std::tuple<int, int>, Tile> loadCSV(const std::string&filename);

    void save_map(std::string& filename, bool& is_already_create);
    void save_spawns(std::string& filename, bool& is_already_create);
    void set_values(Tile& selectedTile, const double& minX, const double& maxX, const double& minY, const double& maxY,
                     SDL_Event& event);

public:
    explicit MapCreator(const std::string& mapName, const double& width, const double& height, const bool& is_already_create);

    void select_map();
    void create_map(std::string& filename, bool& is_already_create);

    MapCreator(const MapCreator&) = delete;
    MapCreator& operator=(const MapCreator&) = delete;

    MapCreator(MapCreator&&) = default;
    MapCreator& operator=(MapCreator&&) = default;

    ~MapCreator() = default;
};

#endif
