#include "headers/map_creator.h"


MapCreator::MapCreator(const std::string& mapName, const double& width, const double& height, const bool& is_already_create):
        mapName(mapName), mapWidth(width), mapHeight(height), window(800, 600), is_already_create(is_already_create) {}

//Pre: -
//Post: Guarda el nuevo mapa en
void MapCreator::save_map(std::string& filename, bool& is_already_create) {

    std::string newFilename = filename;
    std::string path = path_maps + newFilename;
    std::ofstream file(path);
        int fila_anterior = -1;

        if (file.is_open()) {
            for (const auto& pair : mapTiles) {
                const std::tuple<int, int>& key = pair.first;
                const Tile& value = pair.second;
                int fila_actual = std::get<0>(key);

                if (fila_actual != fila_anterior) {
                    if (fila_anterior != -1) {
                        file << "\n";
                    }
                    fila_anterior = fila_actual;
                } else {
                    file << ",";
                }
                file << value.id;
            }
            file.close();
    } else {
        std::cerr << "No se pudo abrir el archivo y por lo tanto no se creó el mapa." << std::endl;
    }
}


//Pre: -
//Post: Formato de guardado: [ID_DE_TIPO_DE_SPAWN(int),FILA(int),COLUMNA(int),ID_elemento_en_tileset(int)]\n
void MapCreator::save_spawns(std::string& filename, bool& is_already_create){

    std::string newFilename = filename + "_spawns";
    std::string path = path_maps + newFilename;

    std::ofstream file(path);
    if (file.is_open()) {
        for (const auto& value : mapSpawn) {
            
            const Tile& tile = value.second;
            int row = std::get<0>(value.first);
            int column = std::get<1>(value.first) - (TILESET_WIDTH*TILE_MAP_ASSETS);
                
            file << tile.type << "," << row << "," << column << "," << tile.id << "\n";
        }
        file.close();
    } else {
        std::cerr << "No se pudo abrir el archivo y por lo tanto no se creó el mapa." << std::endl;
    }
}


//Pre: -
//Post: Carga las posiciones vacias del mapa en un mapa del juego.
std::map<std::tuple<int, int>, Tile> MapCreator::loadEmptyCSV() {

        for(int i = 0; i < mapHeight; i++){
            for(int j = 0; j < mapWidth; j++){
                int tile_id = -1;
                Tile tile;
                tile.id = tile_id;
                tile.srcRect = {0, 0, TILE_MAP_ASSETS, TILE_MAP_ASSETS};
                tile.destRect = {(j*TILE_MAP_CREATED+TILESET_WIDTH*TILE_MAP_ASSETS), i*TILE_MAP_CREATED, TILE_MAP_CREATED, TILE_MAP_CREATED};
                std::tuple<int,int> posicion = std::make_tuple(i, j);
                mapTiles[posicion] = tile;
            }
        }
    return mapTiles;
}


//Pre: -
//Post: Carga en un mapa todos los datos obtenidos del CSV que representa un mapa del juego.
std::map<std::tuple<int, int>, Tile> MapCreator::loadCSV(const std::string& filename) {

    std::string path = path_maps + filename;
    std::cout << path << std::endl;
    std::map<std::tuple<int, int>, Tile> mapTiles;
    std::ifstream file(path);
    if (file.is_open()) {
        std::string line;
        int row = 0;
        int column = 0;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string value;
            column = 0;

            while (std::getline(iss, value, ',')) {
                int tile_id = std::stoi(value);
                Tile tile;
                tile.id = tile_id;
                tile.srcRect = {(tile_id % TILESET_WIDTH)*TILE_MAP_ASSETS, (tile_id / TILESET_WIDTH)*TILE_MAP_ASSETS, TILE_MAP_ASSETS, TILE_MAP_ASSETS};
                tile.destRect = {(column*TILE_MAP_CREATED)+TILESET_WIDTH*TILE_MAP_ASSETS, row*TILE_MAP_CREATED, TILE_MAP_CREATED, TILE_MAP_CREATED};
                std::tuple<int,int> posicion = std::make_tuple(row, column);
                mapTiles[posicion] = tile;
                column++;
            }
            row++;
        }
        mapHeight = row;
        mapWidth = column;
        file.close();
    } else {
        std::cerr << "No se pudo abrir el archivo." << std::endl;
    }
    return mapTiles;
}


//Pre: -
//Post: Guarda en mi matriz mapTile los valores que selecciono de mi paleta de assets para poder crear el mapa.
void MapCreator::set_values(Tile& selectedTile, const double& minX, const double& maxX, const double& minY, const double& maxY, SDL_Event& event){

    std::unique_lock<std::mutex> lock(mtx_map);

    double newX = event.button.x;
    double newY = event.button.y;
                        
    if (newX < minX || newX >= maxX)
        return;

    if (newY < maxY || newY >= minY)
        return;

    int fila = std::floor(newY / TILE_MAP_CREATED) * TILE_MAP_CREATED;
    int columna = std::floor(newX / TILE_MAP_CREATED) * TILE_MAP_CREATED;


    std::tuple<int,int> posicion = std::make_tuple(fila/TILE_MAP_CREATED, (columna-TILESET_WIDTH*TILE_MAP_ASSETS)/TILE_MAP_CREATED);
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
// Post: Si el mapa seleccionado existe, se habre la opcion de modificarlo, y si no existe se puede crear uno nuevo desde cero.
void MapCreator::select_map() {
    bool map_created = false;

    map_created = create_map(mapName, is_already_create);

    if(map_created){
        handle_draw();
    } else {
        std::cout << "Se produjo un error en la creacion del mapa" << std::endl;
    }
}


bool MapCreator::render_assets(){


    int numTiles = (width_texture / TILE_MAP_ASSETS) * (height_texture / TILE_MAP_ASSETS);
    int tilesPerRow = (width_texture / TILE_MAP_ASSETS);
    
    for (int i = 0; i < numTiles; i++) {
        Tile tile;
        tile.id = i;
        tile.srcRect = {(i % tilesPerRow)*TILE_MAP_ASSETS, (i / tilesPerRow)*TILE_MAP_ASSETS, TILE_MAP_ASSETS, TILE_MAP_ASSETS};
        tile.selected = false;
        // cppcheck-suppress uninitStructMember
        tiles_asset.push_back(tile);
    }
    destRectAsset = {0, 0, width_texture, height_texture};
    SDL_RenderCopy(renderer, assetTexture, NULL, &destRectAsset);
    window.render();

    if(is_already_create){
        mapTiles = loadCSV(mapName);
        for (const auto& pair : mapTiles) {
            const Tile& value = pair.second;
            SDL_RenderCopy(renderer, assetTexture, &(value.srcRect), &(value.destRect));
        }
        window.render();
    } else {
        mapTiles = loadEmptyCSV();
        for (const auto& pair : mapTiles) {
            const Tile& value = pair.second;
            SDL_RenderCopy(renderer, assetTexture, &(value.srcRect), &(value.destRect));
        }
        window.render();
    }
    return true;
}

//Pre: -
//Post: -
bool MapCreator::create_map(std::string& filename, bool& is_already_create){

    renderer = window.getRenderer();

    SDL_Surface* tilesetSurface = IMG_Load("../editor_src/assets/ASSETS_GENERALES.png");
    if (tilesetSurface == nullptr) {
        std::cout << "Error al cargar la imagen: " << IMG_GetError() << std::endl;
        return false;
    }
    SDL_SetColorKey(tilesetSurface, SDL_TRUE, SDL_MapRGB(tilesetSurface->format, 87, 0, 203));
    assetTexture = SDL_CreateTextureFromSurface(renderer, tilesetSurface);

    if (assetTexture == nullptr){
        std::cout << "Error al crear la textura: " << SDL_GetError() << std::endl;
        return false;
    }
    SDL_FreeSurface(tilesetSurface);
    SDL_SetTextureBlendMode(assetTexture, SDL_BLENDMODE_BLEND);
    SDL_GetRendererOutputSize(renderer, &window_width, &window_height);
    SDL_QueryTexture(assetTexture, NULL, NULL, &width_texture, &height_texture);

    if(render_assets())
        return true;

    return false;
}



//Pre: -
//Post: -
void MapCreator::handle_draw(){

    int x = 0;
    int y = 0;
    increase = 1;

    bool running = true;
    DrawerEditor drawer(running, tiles_asset, width_texture, mapWidth, mapHeight, TILE_MAP_CREATED, mapSpawn, mapTiles, x, y, increase);
    drawer.start();

    while(running){

        Tile value;
        window.fill();
        //std::cout << "mi x es " << x << "\n";
        //std::cout << "mi y es " << y << "\n";
        if(!mapTiles.empty()){
            for (auto pairMap : mapTiles) {
                value = pairMap.second;
                std::tuple<int, int> pos = pairMap.first;
                int pos_y = std::get<0>(pos);
                int pos_x = std::get<1>(pos);
                SDL_Rect resct_new = {(pos_x*8*increase + (int)x) + TILESET_WIDTH*TILE_MAP_ASSETS, (pos_y*8*increase + (int)y), 8*increase , 8*increase };
                //Aca edito el desRect:
                /*value.destRect.x = (value.destRect.x *increase + (int)x);
                value.destRect.y = (value.destRect.y *increase + (int)y);
                value.destRect.w = value.destRect.w *increase;
                value.destRect.h = value.destRect.h *increase;*/
                //SDL_Rect resct_new = {(value.destRect.x *increase + (int)x), (value.destRect.y *increase + (int)y), value.destRect.w *increase, value.destRect.h *increase};

                SDL_RenderCopy(window.getRenderer(), assetTexture, &(value.srcRect), &(resct_new));
            }
        }

        if(!mapSpawn.empty()){
            for (auto pairSpawn : mapSpawn) {
                value = pairSpawn.second;
                std::tuple<int, int> pos = pairSpawn.first;
                int pos_y = std::get<0>(pos);
                int pos_x = std::get<1>(pos);
                SDL_Rect resct_new = {(pos_x*8*increase + (int)x) + TILESET_WIDTH*TILE_MAP_ASSETS, (pos_y*8*increase + (int)y), 8*increase , 8*increase };
                SDL_RenderCopy(window.getRenderer(), assetTexture, &(value.srcRect), &(resct_new));
            }
        }

        SDL_RenderCopy(window.getRenderer(), assetTexture, NULL, &destRectAsset);
        window.render();

        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }
    drawer.join();
    save_map(mapName, is_already_create);
    save_spawns(mapName, is_already_create);
    mapTiles.clear();
    mapSpawn.clear();
}