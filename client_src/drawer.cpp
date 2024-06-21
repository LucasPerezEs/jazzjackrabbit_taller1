
#include "headers/drawer.h"

Drawer::Drawer(SdlWindow& windows): window(windows) {}

void Drawer::draw_with_camara(const std::vector<std::vector<int>>& tilemap, SDL_Texture* tilesetTexture, Camara* camara) {

    // Ahora recorre solo los tiles que están dentro de la vista de la cámara
    for (long unsigned int y = 0; y < tilemap.size(); y++) {
        for (long unsigned int x = 0; x < tilemap[0].size(); x++) {

            // Obtiene el id del tile
            int tileValue = tilemap[y][x];

            // Calcula la posición del tile en píxeles
            int posX = x;
            int posY = tilemap.size() - y;

            if (!camara->en_rango(posX, posY, 1, 1)) {
                continue;
            }

            SDL_Rect sourceRect;
            sourceRect.x = (tileValue % TILESET_WIDTH) * 16;
            sourceRect.y = (tileValue / TILESET_WIDTH) * 16;
            sourceRect.w = 16;
            sourceRect.h = 16;

            // Define el rectángulo de destino en la pantalla
            SDL_Rect destinationRect;

            destinationRect.x = (posX - camara->x) * camara->escalax;
            destinationRect.y = (camara->y - posY) * camara->escalay;
            destinationRect.w = camara->escalax;
            destinationRect.h = camara->escalay;

            // Renderiza el tile
            SDL_RenderCopy(window.getRenderer(), tilesetTexture, &sourceRect,
                           &destinationRect);
        }
    }
}


void Drawer::draw_map(std::map<std::tuple<int, int>, Tile>& tilemap, SDL_Texture* tilesetTexture, const int& size_src, const int& size_dest) {

    // Ahora recorre solo los tiles que están dentro de la vista de la cámara
    for (const auto& tileEntry : tilemap) {
        const auto& tilePosition = tileEntry.first;
        const Tile& tile = tileEntry.second;

        // Calcula la posición del tile en píxeles
        int posX = std::get<0>(tilePosition);
        int posY = std::get<1>(tilePosition);

        SDL_Rect sourceRect;
        sourceRect.x = (tile.id % TILESET_WIDTH) * size_src;
        sourceRect.y = (tile.id / TILESET_WIDTH) * size_src;
        sourceRect.w = size_src;
        sourceRect.h = size_src;

        // Define el rectángulo de destino en la pantalla
        SDL_Rect destinationRect;

        destinationRect.x = posX;
        destinationRect.y = posY;
        destinationRect.w = size_dest;
        destinationRect.h = size_dest;

        // Renderiza el tile
        SDL_RenderCopy(window.getRenderer(), tilesetTexture, &sourceRect, 
            &destinationRect);
    }
}