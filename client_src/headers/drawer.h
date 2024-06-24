#ifndef DRAWER_H
#define DRAWER_H

#include <cmath>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include <SDL2/SDL.h>
#include "SdlWindow.h"
#include "camara.h"
#include "tile.h"

const int TILESET_WIDTH = 10;

class Drawer {
private:
    SdlWindow& window;

public:
    explicit Drawer(SdlWindow& window);

    void draw_with_camara(const std::vector<std::vector<std::string>>& tilemap, SDL_Texture* tilesetTexture, Camara* camara);

    Drawer(const Drawer&) = delete;
    Drawer& operator=(const Drawer&) = delete;

    Drawer(Drawer&&) = default;
    Drawer& operator=(Drawer&&) = default;

    ~Drawer() = default;
};

#endif