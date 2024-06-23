#include "headers/map_creator.h"

MapCreator::MapCreator(const std::string& mapName, const double& width, const double& height, const bool& is_already_create):
        mapName(mapName), mapWidth(width), mapHeight(height), window(800, 600), is_already_create(is_already_create) {}

//Pre: -
//Post: Guarda el nuevo mapa en
void MapCreator::save_map(std::string& filename, bool& is_already_create) {

    std::string newFilename = filename;
    if (is_already_create)
        newFilename = newFilename + "_modified";

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

    if (is_already_create)
        newFilename = newFilename + "_modified";
    
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
//Post: Guarda en mi matriz mapTile los valores que selecciono de mi paleta de assets para poder crear el mapa.
void MapCreator::set_values(Tile& selectedTile, const double& minX, const double& maxX, const double& minY, const double& maxY, SDL_Event& event){

    double newX = event.button.x;
    double newY = event.button.y;
                        
    // Me aseguro de que newX está por fuera de la imagen del asset y dentro de la ventana en X.
    if (newX < minX || newX >= maxX)
        return;

    // Me aseguro de que newY está dentro de la ventana en Y
    if (newY < maxY || newY >= minY)
        return;

    int fila = std::floor(newY / TILE_MAP_CREATED) * TILE_MAP_CREATED;
    int columna = std::floor(newX / TILE_MAP_CREATED) * TILE_MAP_CREATED;


    std::tuple<int,int> posicion = std::make_tuple(fila/TILE_MAP_CREATED, (columna-TILESET_WIDTH*TILE_MAP_ASSETS)/TILE_MAP_CREATED);
    std::cout << "Fila: " << fila/TILE_MAP_CREATED << " / Columna: " << (columna-TILESET_WIDTH*TILE_MAP_ASSETS)/TILE_MAP_CREATED << std::endl;

    selectedTile.destRect = { columna, fila, TILE_MAP_CREATED, TILE_MAP_CREATED };

    int PlayerSpawn = 0;
    int EnemySpawn = 1;

    //SPAWN JUGADOR
    if(selectedTile.id == 48 || selectedTile.id == 49 || selectedTile.id == 58 || selectedTile.id == 59){
        selectedTile.type = PlayerSpawn;
        mapSpawn[posicion] = selectedTile;
        return;
    }

    //SPAWN ENEMIGO
    if(selectedTile.id == 68 || selectedTile.id == 69 || selectedTile.id == 78 || selectedTile.id == 79){
        selectedTile.type = EnemySpawn;
        mapSpawn[posicion] = selectedTile;
        return;
    }

    //Que pasas si quiero dibujar algo de mapa por sobre un spawn?
    //Debo chequear si ese elemento esta en el spawn y si esta, lo borro.
    if (mapSpawn.find(posicion) != mapSpawn.end())
        mapSpawn.erase(posicion);

    mapTiles[posicion] = selectedTile;
}



// Pre: -
// Post: Si el mapa seleccionado existe, se habre la opcion de modificarlo, y si no existe se puede crear uno nuevo desde cero.
void MapCreator::select_map() {

    //std::string mapName;
    //bool is_already_create = false;
    //std::cout << "Por favor, ingresa el nombre del nuevo mapa: ";
    //std::cin >> mapName;
    //if (mapName == "1")
      //  mapName = "castle_earlong_mapa";

    //if (std::ifstream(mapName)) {
      //  std::cout << "El mapa con el nombre '" << mapName << "' ya existe." << std::endl;
      //  is_already_create = true;
    //}
    create_map(mapName, is_already_create);
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
//Post: -
void MapCreator::create_map(std::string& filename, bool& is_already_create){

    mapTiles.clear();
    std::vector<Tile> tiles_asset;
    std::tuple<int, int> posicion;
    SDL_Renderer* renderer = this->window.getRenderer();

    SDL_Surface* tilesetSurface = IMG_Load("../editor_src/assets/ASSETS_GENERALES.png");
    if (tilesetSurface == nullptr) {
        std::cout << "Error al cargar la imagen: " << IMG_GetError() << std::endl;
        return;
    }
    SDL_SetColorKey(tilesetSurface, SDL_TRUE, SDL_MapRGB(tilesetSurface->format, 87, 0, 203));

    SDL_Texture* assetTexture = SDL_CreateTextureFromSurface(renderer, tilesetSurface);

    if (assetTexture == nullptr)
        std::cout << "Error al crear la textura: " << SDL_GetError() << std::endl;

    SDL_FreeSurface(tilesetSurface);
    SDL_SetTextureBlendMode(assetTexture, SDL_BLENDMODE_BLEND);

    int window_width, window_height;
    SDL_GetRendererOutputSize(renderer, &window_width, &window_height);

    int width_texture, height_texture;
    SDL_QueryTexture(assetTexture, NULL, NULL, &width_texture, &height_texture);

    std::cout << width_texture << std::endl;
    

    //Renderizo la paleta de assets
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
    SDL_Rect destRectAsset = {0, 0, width_texture, height_texture};
    SDL_RenderCopy(renderer, assetTexture, NULL, &destRectAsset);
    this->window.render();

    if(is_already_create){
        mapTiles = loadCSV(filename);
        for (const auto& pair : mapTiles) {
            const Tile& value = pair.second;
            SDL_RenderCopy(renderer, assetTexture, &(value.srcRect), &(value.destRect));
        }
        this->window.render();
    } else {
        mapTiles = loadEmptyCSV();
        for (const auto& pair : mapTiles) {
            const Tile& value = pair.second;
            SDL_RenderCopy(renderer, assetTexture, &(value.srcRect), &(value.destRect));
        }
        this->window.render();
    }

    SDL_Point mousePos;
    Tile selectedTile;

    bool running = true;
    bool mouseHeldDown = false;
    selectedTile.selected = false;

    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {

                case SDL_QUIT:
                    running = false;
                    break;

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
                    set_values(selectedTile, width_texture, width_texture+mapWidth*TILE_MAP_CREATED, mapHeight*TILE_MAP_CREATED, 0, event);
                    mouseHeldDown = true;
                    break;
                }

                case SDL_MOUSEBUTTONUP: {
                    mouseHeldDown = false;
                    break;
                }

                case SDL_MOUSEMOTION: {
                    if(mouseHeldDown)
                        set_values(selectedTile, width_texture, width_texture+mapWidth*TILE_MAP_CREATED, mapHeight*TILE_MAP_CREATED, 0, event);
                }
            }
                this->window.fill();

            Tile value;
            for (const auto& pairMap : mapTiles) {
                value = pairMap.second;
                SDL_RenderCopy(renderer, assetTexture, &(value.srcRect), &(value.destRect));
            }

            for (const auto& pairSpawn : mapSpawn) {
                value = pairSpawn.second;
                SDL_RenderCopy(renderer, assetTexture, &(value.srcRect), &(value.destRect));
            }

            SDL_RenderCopy(renderer, assetTexture, NULL, &destRectAsset);
            this->window.render();
        }
    }
    save_map(filename, is_already_create);
    save_spawns(filename, is_already_create);
    
}