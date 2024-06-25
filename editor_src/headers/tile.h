
#ifndef TILE_H
#define TILE_H

#include <map>
#include <cmath>
#include <chrono>
#include <fstream>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>
#include <mutex>
#include <iostream>
#include <condition_variable>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "SdlWindow.h"
#include "../../common_src/headers/thread.h"

const int TILESET_WIDTH = 10;

struct Tile {
    // cppcheck-suppress unusedStructMember
    int id;  // ID del tile en el tileset
    // cppcheck-suppress unusedStructMember
    int type;
    SDL_Rect srcRect;
    SDL_Rect destRect;
    // cppcheck-suppress unusedStructMember
    bool selected;  // Indica si el tile está seleccionado
};

#endif