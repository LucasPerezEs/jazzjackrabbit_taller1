#ifndef MAPCREATOR_H
#define MAPCREATOR_H

#include "drawer_editor.h"

#define TILE_MAP_ASSETS 48  // Tamaño en el que se ve el asset al crear.
#define TILE_MAP_CREATED 48  // Tamaño en el que se ve el mapa al crearlo.

class MapCreator {
    std::string mapName;
    double mapWidth;
    double mapHeight;
    SdlWindow window;
    SDL_Renderer* renderer;
    SDL_Texture* assetTexture;
    bool is_already_create;

    int window_width;
    int window_height;
    int width_texture;
    int height_texture;
    SDL_Rect destRectAsset;

    std::mutex mtx_map;
    std::condition_variable is_not_pointed_map;
    std::string path_maps = "../server_src/maps/";

    std::vector<Tile> tiles_asset;
    std::map<std::tuple<int, int>, Tile> mapTiles;
    std::map<std::tuple<int, int>, Tile> mapSpawn;

    std::map<std::tuple<int, int>, Tile> loadEmptyCSV();
    std::map<std::tuple<int, int>, Tile> loadCSV(const std::string&filename);

    bool render_assets();
    void save_map(std::string& filename, bool& is_already_create);
    void save_spawns(std::string& filename, bool& is_already_create);
    void set_values(Tile& selectedTile, const double& minX, const double& maxX, const double& minY, const double& maxY,
                     SDL_Event& event);

public:
    explicit MapCreator(const std::string& mapName, const double& width, const double& height, const bool& is_already_create);

    void select_map();
    void handle_draw();
    bool create_map(std::string& filename, bool& is_already_create);

    MapCreator(const MapCreator&) = delete;
    MapCreator& operator=(const MapCreator&) = delete;

    MapCreator(MapCreator&&) = default;
    MapCreator& operator=(MapCreator&&) = default;

    ~MapCreator() = default;
};

#endif
