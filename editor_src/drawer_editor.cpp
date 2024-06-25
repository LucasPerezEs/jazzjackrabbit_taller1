
#include "headers/drawer_editor.h"
#include <chrono>

// Pre: -
// Post: -
DrawerEditor::DrawerEditor(SdlWindow& window, SDL_Texture* assetTexture, SDL_Rect& destRectAsset, std::map<std::tuple<int, int>, Tile>& mapTiles, std::map<std::tuple<int, int>, Tile>& mapSpawn, 
    std::mutex& mtx_map, std::condition_variable& is_not_pointed_map, bool& running):
    window(window), assetTexture(assetTexture), destRectAsset(destRectAsset), mapTiles(mapTiles), mapSpawn(mapSpawn), mtx_map(mtx_map), is_not_pointed_map(is_not_pointed_map), running(running) {}


void DrawerEditor::run(){

    SDL_Renderer* render = window.getRenderer();
    while(running){

        Tile value;
        window.fill();

        if(!mapTiles.empty()){
            for (auto pairMap : mapTiles) {
                value = pairMap.second;
                SDL_RenderCopy(render, assetTexture, &(value.srcRect), &(value.destRect));
            }
        }

        if(!mapSpawn.empty()){
            for (auto pairSpawn : mapSpawn) {
                value = pairSpawn.second;
                SDL_RenderCopy(render, assetTexture, &(value.srcRect), &(value.destRect));
            }
        }

        SDL_RenderCopy(render, assetTexture, NULL, &destRectAsset);
        window.render();

        std::this_thread::sleep_for(std::chrono::milliseconds(17));
    }
}
