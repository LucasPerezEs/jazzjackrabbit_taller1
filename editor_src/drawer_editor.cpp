
#include "headers/drawer_editor.h"


void set_values(Tile& selectedTile, const double& minX, const double& maxX, const double& minY, const double& maxY,
 SDL_Event& event, int TILE_MAP_CREATED, int TILE_MAP_ASSETS, std::map<std::tuple<int, int>, Tile>& mapSpawn, std::map<std::tuple<int, int>, Tile>& mapTiles, float& x, float& y, int& increase){

    //std::unique_lock<std::mutex> lock(mtx_map);

    double newX = (event.button.x + x);
    double newY = (event.button.y - y);
                        
    //if (newX < minX || newX >= maxX)
      //  return;

    //if (newY < maxY || newY >= minY)
      //  return;

    int fila = std::floor(newY / (TILE_MAP_CREATED)) * (TILE_MAP_CREATED);
    int columna = std::floor(newX / (TILE_MAP_CREATED)) * (TILE_MAP_CREATED);


    std::tuple<int,int> posicion = std::make_tuple(fila/(TILE_MAP_CREATED), (columna-TILESET_WIDTH*TILE_MAP_ASSETS)/(TILE_MAP_CREATED));
    selectedTile.destRect = { columna, fila, TILE_MAP_CREATED, TILE_MAP_CREATED };

    int PlayerSpawn = 0;
    int EnemySpawn = 1;

    //SPAWN PLAYER
    if(selectedTile.id == 48 || selectedTile.id == 49 || selectedTile.id == 58 || selectedTile.id == 59){
        selectedTile.type = PlayerSpawn;
        mapSpawn[posicion] = selectedTile;
        return;

    //SPAWN ENEMY
    } else if(selectedTile.id == 68 || selectedTile.id == 69 || selectedTile.id == 78 || selectedTile.id == 79){
        selectedTile.type = EnemySpawn;
        mapSpawn[posicion] = selectedTile;
        return;
    } 

    if (mapSpawn.count(posicion) > 0)
        mapSpawn.erase(posicion);

    mapTiles[posicion] = selectedTile;
}


// Pre: -
// Post: -
DrawerEditor::DrawerEditor(bool& running, std::vector<Tile>& tiles_asset, int width_texture, int mapWidth, int mapHeight, int TILE_MAP_CREATED, std::map<std::tuple<int, int>, Tile>& mapSpawn, std::map<std::tuple<int, int>, Tile>& mapTiles, float& x, float& y, int& increase):
 tiles_asset(tiles_asset), running(running), mapSpawn(mapSpawn), mapTiles(mapTiles), x(x), y(y), increase(increase) {
    this->width_texture = width_texture;
    this->mapWidth = mapWidth;
    this->mapHeight = mapHeight;
    this->TILE_MAP_CREATED = TILE_MAP_CREATED;
    this->scale_value = 8;
 }



void DrawerEditor::handle_keydown(const SDL_Event& event) {
    const SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&)event;

    switch (keyEvent.keysym.sym) {
        case SDLK_w:
            y--;
            //cmd.action = Command::UP;
            break;
        case SDLK_s:
            y++;
            //cmd.action = Command::DOWN;
            break;
        case SDLK_a:
            x--;
            //cmd.action = Command::LEFT;
            break;
        case SDLK_d:
            x++;
            //cmd.action = Command::RIGHT;
            break;

        case SDLK_z:
            increase++;
            break;

        case SDLK_x:
            if(increase > 1){
                increase--;
            }
            break;

        }}
        


void DrawerEditor::run() {

    SDL_Event event;
    Tile selectedTile;
    SDL_Point mousePos;


    bool mouseHeldDown = false;
    selectedTile.selected = false;

    while (running) {
       SDL_WaitEvent(&event);
        switch (event.type) {

            case SDL_QUIT: {
                running = false;
                break;
            }
            case SDL_MOUSEBUTTONDOWN: {
                mousePos.x = event.button.x;
                mousePos.y = event.button.y;
                for (auto& tile : tiles_asset) {
                    if (SDL_PointInRect(&mousePos, &tile.srcRect)) {
                        selectedTile = tile;
                        selectedTile.selected = true;
                        break;
                    }
                }
                if (!selectedTile.selected)
                    break;
                set_values(selectedTile, width_texture, width_texture+mapWidth*TILE_MAP_CREATED, mapHeight*TILE_MAP_CREATED, 0, event, TILE_MAP_CREATED, 16, mapSpawn, mapTiles, x, y, increase);
                mouseHeldDown = true;
                break;
            }

            case SDL_MOUSEBUTTONUP: {
                mouseHeldDown = false;
                break;
            }

            case SDL_MOUSEMOTION: {
                if(mouseHeldDown)
                    set_values(selectedTile, width_texture, width_texture+mapWidth*TILE_MAP_CREATED, mapHeight*TILE_MAP_CREATED, 0, event, TILE_MAP_CREATED, 16, mapSpawn, mapTiles, x, y, increase);
                }
            case SDL_KEYDOWN: {
                handle_keydown(event);
                break;
        }
    }







    /*SDL_Renderer* render = window.getRenderer();
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

        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }*/
}
}
