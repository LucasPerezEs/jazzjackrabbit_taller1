
#include "headers/drawer_editor.h"

// Pre: -
// Post: -
DrawerEditor::DrawerEditor(SdlWindow& window, SDL_Texture* assetTexture, SDL_Rect& destRectAsset, std::map<std::tuple<int, int>, Tile>& mapTiles, std::map<std::tuple<int, int>, Tile>& mapSpawn, 
    std::mutex& mtx_map, std::condition_variable& is_not_pointed_map, bool& running):
    window(window), assetTexture(assetTexture), destRectAsset(destRectAsset), mapTiles(mapTiles), mapSpawn(mapSpawn), mtx_map(mtx_map), is_not_pointed_map(is_not_pointed_map), running(running) {}


void DrawerEditor::run(){

    while(running){

        std::unique_lock<std::mutex> lock(mtx_map);

        Tile value;
        window.fill();

        for (const auto& pairMap : mapTiles) {
            value = pairMap.second;
            SDL_RenderCopy(window.getRenderer(), assetTexture, &(value.srcRect), &(value.destRect));
        }

        for (const auto& pairSpawn : mapSpawn) {
            value = pairSpawn.second;
            SDL_RenderCopy(window.getRenderer(), assetTexture, &(value.srcRect), &(value.destRect));
        }

        SDL_RenderCopy(window.getRenderer(), assetTexture, NULL, &destRectAsset);
        window.render();

        is_not_pointed_map.wait(lock);
    }
}
