#ifndef MAPCREATOR_H
#define MAPCREATOR_H

#include "drawer_editor.h"

#define TILE_MAP_ASSETS 16 
 
#define TILE_MAP_CREATED 8

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

    int increase;
    std::mutex mtx_map;
    std::condition_variable is_not_pointed_map;
    std::string path_maps = "../server_src/maps/";

    std::vector<Tile> tiles_asset;
    std::map<std::tuple<int, int>, Tile> mapTiles;
    std::map<std::tuple<int, int>, Tile> mapSpawn;

    std::map<std::tuple<int, int>, Tile> loadEmptyCSV();
    std::map<std::tuple<int, int>, Tile> loadCSV(const std::string&filename);
    std::map<std::tuple<int, int>, Tile> load_spawns(const std::string& filename);

    bool render_assets();
    void save_map(std::string& filename, bool& is_already_create);
    void save_spawns(std::string& filename, bool& is_already_create);


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
