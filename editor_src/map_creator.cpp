#include "headers/map_creator.h"

MapCreator::MapCreator(const std::string& mapName, const double& width, const double& height, const bool& is_already_create):
        mapName(mapName), mapWidth(width), mapHeight(height), window(800, 600), is_already_create(is_already_create) {}

//Pre: -
//Post: Guarda el nuevo mapa en
void MapCreator::save_map(std::string& filename, bool& is_already_create) {

    std::string newFilename = filename;
    if (is_already_create)
        newFilename = filename + "_modified";

    std::string path = path_maps + newFilename;
    std::ofstream file(path);

    if (file.is_open()) {
        
        for (int fila = 0; fila < mapHeight; ++fila) {
    for (int columna = 0; columna < mapWidth; ++columna) {
        const Tile& value = mapTiles[{fila, columna}];

        if (columna > 0) {
            file << ",";
        }
        file << value.id;
    }
    file << "\n";
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
    if (newX < minX || newX > maxX)
        return;

    // Me aseguro de que newY está dentro de la ventana en Y
    if (newY < maxY || newY > minY)
        return;

    int multiploX = std::floor(newX / TILE_MAP_CREATED) * TILE_MAP_CREATED;
    int multiploY = std::floor(newY / TILE_MAP_CREATED) * TILE_MAP_CREATED;

    std::tuple<int,int> posicion = std::make_tuple(multiploY, multiploX);
    selectedTile.destRect = { multiploX, multiploY, TILE_MAP_CREATED, TILE_MAP_CREATED };

    //
    if (mapTiles.find(posicion) != mapTiles.end()) {

        const Tile& tile_found = mapTiles[posicion];
        if(selectedTile.id == 48 || selectedTile.id == 49 || selectedTile.id == 58 || selectedTile.id == 59)
            selectedTile.id = tile_found.id;

        if(selectedTile.id == 68 || selectedTile.id == 69 || selectedTile.id == 78 || selectedTile.id == 79)
            selectedTile.id = tile_found.id;

        //48,49,58,59 es para posicion del jugador.
        //68,69,78,79 es para los spawn points.

    } else {
        
        //No puedo colocar un spawn point en un sector no inicializado del mapa.
        if(selectedTile.id == 48 || selectedTile.id == 49 || selectedTile.id == 58 || selectedTile.id == 59)
            return;
    }

    mapTiles[posicion] = selectedTile;
    //mapTiles[posicion] = selectedTile;
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
                tile.srcRect = {0,0,TILE_MAP_ASSETS, TILE_MAP_ASSETS};
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
            column = 20;

            while (std::getline(iss, value, ',')) {

                int tile_id = std::stoi(value);
                Tile tile;
                tile.id = tile_id;
                tile.srcRect = {(tile_id % TILESET_WIDTH)*TILE_MAP_ASSETS, (tile_id / TILESET_WIDTH)*TILE_MAP_ASSETS, TILE_MAP_ASSETS, TILE_MAP_ASSETS};
                tile.destRect = {column*TILE_MAP_CREATED, row*TILE_MAP_CREATED, TILE_MAP_CREATED, TILE_MAP_CREATED};
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
                        //set_values(selectedTile, width_texture, (window_width*mapWidth/100), (window_height*mapHeight/100), 0, event);
                        set_values(selectedTile, width_texture, width_texture+mapWidth*TILE_MAP_CREATED, mapHeight*TILE_MAP_CREATED, 0, event);
                }
            }
                this->window.fill();

            for (const auto& pair : mapTiles) {
                const Tile& value = pair.second;
                SDL_RenderCopy(renderer, assetTexture, &(value.srcRect), &(value.destRect));
            }

            SDL_RenderCopy(renderer, assetTexture, NULL, &destRectAsset);
            this->window.render();
        }
    }
    save_map(filename, is_already_create);
    
}