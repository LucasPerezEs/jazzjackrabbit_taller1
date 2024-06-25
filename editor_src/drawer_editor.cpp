
#include "headers/drawer_editor.h"


void set_values(Tile& selectedTile, const double& minX, const double& maxX, const double& minY, const double& maxY,
 SDL_Event& event, int TILE_MAP_CREATED, int TILE_MAP_ASSETS, std::map<std::tuple<int, int>, Tile>& mapSpawn, std::map<std::tuple<int, int>, Tile>& mapTiles, int& x, int& y, int& increase, int mapWidth, int mapHeight){

    int newX = (event.button.x - x - TILESET_WIDTH*TILE_MAP_ASSETS);
    int newY = (event.button.y - y);

    int fila = std::floor(newY / (TILE_MAP_CREATED*increase));
    int columna = std::floor(newX / (TILE_MAP_CREATED*increase));

    if (fila < 0 || fila > mapWidth-1 || columna < 0 || columna > mapHeight-1)
        return;

    std::tuple<int,int> posicion = std::make_tuple(fila, columna);

    int PlayerSpawn = 0;
    int EnemySpawn1 = 1;
    int EnemySpawn2 = 2;
    int EnemySpawn3 = 3;
    int GemSpawn = 4;
    int CoinSpawn = 5;

    //SPAWN PLAYER
    if(selectedTile.id == 178 || selectedTile.id == 179 || selectedTile.id == 188 || selectedTile.id == 189){
        selectedTile.type = PlayerSpawn;
        mapSpawn[posicion] = selectedTile;
        return;

    //SPAWN ENEMY1
    } else if(selectedTile.id == 198 || selectedTile.id == 199 || selectedTile.id == 208 || selectedTile.id == 209){
        selectedTile.type = EnemySpawn1;
        mapSpawn[posicion] = selectedTile;
        return;
    } 

    //SPAWN ENEMY2
     else if(selectedTile.id == 238 || selectedTile.id == 239 || selectedTile.id == 248 || selectedTile.id == 249){
        selectedTile.type = EnemySpawn2;
        mapSpawn[posicion] = selectedTile;
        return;
    }

    //SPAWN ENEMY3
     else if(selectedTile.id == 258 || selectedTile.id == 259 || selectedTile.id == 268 || selectedTile.id == 269){
        selectedTile.type = EnemySpawn3;
        mapSpawn[posicion] = selectedTile;
        return;
    } 

    //GEMA
    else if(selectedTile.id == 218 || selectedTile.id == 219 || selectedTile.id == 228 || selectedTile.id == 229){
        selectedTile.type = GemSpawn;
        mapSpawn[posicion] = selectedTile;
        return;
    } 
    //COIN
    else if(selectedTile.id == 158 || selectedTile.id == 159 || selectedTile.id == 168 || selectedTile.id == 169){
        selectedTile.type = CoinSpawn;
        mapSpawn[posicion] = selectedTile;
        return;
    } 

    if (mapSpawn.count(posicion) > 0)
        mapSpawn.erase(posicion);

    mapTiles[posicion] = selectedTile;
}

void delete_spawn(SDL_Event event, std::map<std::tuple<int, int>, Tile>& mapSpawn, int TILE_MAP_CREATED, int TILE_MAP_ASSETS, int& x, int& y, int increase) {

    int newX = (event.button.x - x - TILESET_WIDTH*TILE_MAP_ASSETS);
    int newY = (event.button.y - y);

    int fila = std::floor(newY / (TILE_MAP_CREATED*increase));
    int columna = std::floor(newX / (TILE_MAP_CREATED*increase));

    for (auto spawn: mapSpawn) {
        if (fila == std::get<0>(spawn.first) && columna == std::get<1>(spawn.first)) {
            mapSpawn.erase(spawn.first);
            break;
        }
    }
}

// Pre: -
// Post: -
DrawerEditor::DrawerEditor(bool& running, std::vector<Tile>& tiles_asset, int width_texture, int mapWidth, int mapHeight, int TILE_MAP_CREATED, std::map<std::tuple<int, int>, Tile>& mapSpawn, std::map<std::tuple<int, int>, Tile>& mapTiles, int& x, int& y, int& increase):
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
            y = y - increase*2;
            break;
        case SDLK_s:
            y = y + increase*2;
            break;
        case SDLK_a:
            x = x - increase*2;
            break;
        case SDLK_d:
            x = x + increase*2;
            break;

        case SDLK_z:
            increase++;
            break;

        case SDLK_x:
            if(increase > 1){
                increase--;
            }
            break;
    }
}


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
                if (event.button.button == SDL_BUTTON_LEFT) {
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
                    set_values(selectedTile, width_texture, width_texture+mapWidth*TILE_MAP_CREATED, mapHeight*TILE_MAP_CREATED, 0, event, TILE_MAP_CREATED, 16, mapSpawn, mapTiles, x, y, increase, mapWidth, mapHeight);
                    mouseHeldDown = true;
                    break;
                }
                else if (event.button.button == SDL_BUTTON_RIGHT) {
                    delete_spawn(event, mapSpawn, TILE_MAP_CREATED, 16, x, y, increase);
                }
            }

            case SDL_MOUSEBUTTONUP: {
                mouseHeldDown = false;
                break;
            }

                case SDL_MOUSEMOTION: {
                if(event.button.x <= width_texture)
                    break;
                
                if(mouseHeldDown)
                    set_values(selectedTile, width_texture, width_texture+mapWidth*TILE_MAP_CREATED, mapHeight*TILE_MAP_CREATED, 0, event, TILE_MAP_CREATED, 16, mapSpawn, mapTiles, x, y, increase, mapWidth, mapHeight);
            }


            case SDL_KEYDOWN: {
                handle_keydown(event);
                break;
            }
        }

    }
}
