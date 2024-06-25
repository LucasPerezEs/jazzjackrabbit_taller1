#ifndef DRAWER_EDITOR_H
#define DRAWER_EDITOR_H

#include "tile.h"

class DrawerEditor: public Thread {

private:
    std::vector<Tile>& tiles_asset;
    bool& running;
    int width_texture;
    int mapWidth;
    int mapHeight;
    int TILE_MAP_CREATED;
    std::map<std::tuple<int, int>, Tile>& mapSpawn;
    std::map<std::tuple<int, int>, Tile>& mapTiles;
    int scale_value;
    int& x;
    int& y;
    int& increase;

    void handle_keydown(const SDL_Event& event);

public:
    DrawerEditor(bool& running, std::vector<Tile>& tiles_asset, int width_texture, int mapWidth, 
        int mapHeight, int TILE_MAP_CREATED, std::map<std::tuple<int, int>, Tile>& mapSpawn, std::map<std::tuple<int, int>, Tile>& mapTiles, int& x, int& y, int& increase);

    virtual void run() override;

    void close();

    DrawerEditor(const DrawerEditor&) = delete;
    DrawerEditor& operator=(const DrawerEditor&) = delete;

    DrawerEditor(DrawerEditor&&) = default;
    DrawerEditor& operator=(DrawerEditor&&) = default;
};

#endif
