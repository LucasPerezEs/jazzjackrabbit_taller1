
#ifndef TILE_H
#define TILE_H

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

#endif