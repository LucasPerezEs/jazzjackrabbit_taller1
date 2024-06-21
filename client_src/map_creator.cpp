
#include "headers/map_creator.h"

MapCreator::MapCreator(Client& client):
        client(client),
        window(800, 600) {}


//ESTE ESTA MAL. No deberia manrse el path, si no el nombre del mapa nada mas. Se debe de borra este metodo y suplantarlo por loadCSV.
std::vector<std::vector<int>> MapCreator::cargarCSV(const std::string& ruta) {
    std::vector<std::vector<int>> matriz;
    std::ifstream archivo(ruta);

    if (archivo.is_open()) {
        std::string linea;
        while (std::getline(archivo, linea)) {
            std::vector<int> fila;
            std::stringstream ss(linea);
            std::string valor;
            while (std::getline(ss, valor, ',')) {
                fila.push_back(std::stoi(valor));
            }
            matriz.push_back(fila);
        }
        archivo.close();
    }
    return matriz;
}


//Pre: -
//Post: -
void MapCreator::saveMapToCSV(std::string& filename, bool& is_already_create) {

    std::string newFilename;
    std::string extension = ".csv"; // Extensión del archivo

    if (is_already_create) {
        std::string filenameModified;

        size_t extensionPos = filename.find(extension);
        if (extensionPos != std::string::npos) {
            std::string nameBase = filename.substr(0, extensionPos);

            newFilename = nameBase + "_modified" + extension;

        } else {
            std::cerr << "Error: El archivo no tiene la extensión esperada." << std::endl;
            return; 
        }

    } else if(!is_already_create){
        newFilename = filename + extension;
    }
        std::ofstream file(newFilename);
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
//Post: Guarda en mi matriz mapTile los valores que selecciono de mi paleta de assets para poder crear el mapa.
void MapCreator::save_values(Tile& selectedTile, const double& minX, const double& maxX, const double& minY, const double& maxY, SDL_Event& event){

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

    mapTiles[posicion] = selectedTile;
}



// Pre: -
// Post: Si el mapa seleccionado existe, se habre la opcion de modificarlo, y si no existe se puede crear uno nuevo desde cero.
void MapCreator::select_map() {

    std::string mapName;
    bool is_already_create = false;
    //std::cout << "Por favor, ingresa el nombre del nuevo mapa: ";
    //std::cin >> mapName;
    //if (mapName == "1") {
        mapName = "castle_earlong_mapa.csv";
    //}

    if (std::ifstream(mapName)) {
        std::cout << "El mapa con el nombre '" << mapName << "' ya existe." << std::endl;
        is_already_create = true;
    }
    create_map(mapName, is_already_create);
}


//Pre: -
//Post: Carga en un mapa todos los datos obtenidos del CSV que representa un mapa del juego.
std::map<std::tuple<int, int>, Tile> MapCreator::loadCSV(const std::string& filename) {

    std::cout << "Estoy DENTRO de loadCSV " << std::endl;
    std::cout << "FIlename: " << filename << std::endl;

    std::map<std::tuple<int, int>, Tile> mapTiles;
    std::ifstream file(filename);
    if (file.is_open()) {
        std::cout << "Paso 1 " << std::endl;
        std::string line;
        int row = 0;
        while (std::getline(file, line)) {

            std::cout << "En el while de row " << std::endl;
            std::istringstream iss(line);
            std::string value;
            int column = 20;

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
            column = 20;
            row++;
        }
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

    SDL_Surface* tilesetSurface =
            IMG_Load("../client_src/assets/background/ASSETS_GENERALES.png");
    if (tilesetSurface == nullptr) {
        std::cout << "Error al cargar la imagen: " << IMG_GetError() << std::endl;
        return;
    }
    SDL_SetColorKey(tilesetSurface, SDL_TRUE, SDL_MapRGB(tilesetSurface->format, 87, 0, 203));

    SDL_Texture* assetTexture = SDL_CreateTextureFromSurface(renderer, tilesetSurface);

    if (assetTexture == nullptr)
        std::cout << "Error al crear la textura: " << SDL_GetError() << std::endl;

    SDL_FreeSurface(tilesetSurface);
    //SDL_SetTextureBlendMode(assetTexture, SDL_BLENDMODE_BLEND);

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
                    save_values(selectedTile, width_texture, window_width, window_height, 0, event);
                    mouseHeldDown = true;
                    break;
                }

                case SDL_MOUSEBUTTONUP: {
                    mouseHeldDown = false;
                    break;
                }

                case SDL_MOUSEMOTION: {
                    if(mouseHeldDown)
                        save_values(selectedTile, width_texture, window_width, window_height, 0, event);
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
    saveMapToCSV(filename, is_already_create);
    
}