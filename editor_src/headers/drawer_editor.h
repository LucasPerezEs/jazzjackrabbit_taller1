#ifndef DRAWER_EDITOR_H
#define DRAWER_EDITOR_H

#include "tile.h"

class DrawerEditor: public Thread {

private:

    SdlWindow window;
    SDL_Texture* assetTexture;
    SDL_Rect& destRectAsset;
    std::map<std::tuple<int, int>, Tile>& mapTiles;
    std::map<std::tuple<int, int>, Tile>& mapSpawn;

    std::mutex& mtx_map;
    std::condition_variable& is_not_pointed_map;
    bool& running;

public:
    DrawerEditor(SdlWindow& window, SDL_Texture* assetTexture, SDL_Rect& destRectAsset, std::map<std::tuple<int, int>, Tile>& mapTiles, std::map<std::tuple<int, int>, Tile>& mapSpawn,
        std::mutex& mtx_map, std::condition_variable& is_not_pointed_map, bool& running);

    virtual void run() override;

    void close();

    DrawerEditor(const DrawerEditor&) = delete;
    DrawerEditor& operator=(const DrawerEditor&) = delete;

    DrawerEditor(DrawerEditor&&) = default;
    DrawerEditor& operator=(DrawerEditor&&) = default;
};

#endif
