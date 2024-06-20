
#include "headers/map_creator.h"

MapCreator::MapCreator(Client& client):
        client(client),
        window(800, 600) {}


//Pre: -
//Post: -
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
//Post: Modifica SaveMapToCSV para guardar los IDs de los tiles
void MapCreator::SaveMapToCSV(std::ofstream& file, bool& is_already_create) {

    if(is_already_create){

        std::cerr << "No se implemento aun que pasa con el modify" << std::endl;

    } else {

        if (file.is_open()) {
            int fila_anterior = -1;  // Mueve la declaración aquí

        for (const auto& pair : mapTiles) {
            const std::tuple<int, int>& key = pair.first;
            const Tile& value = pair.second;
            int fila_actual = std::get<0>(key);

            if (fila_actual != fila_anterior) {
                if (fila_anterior != -1)
                    file << "\n";  // Utiliza "\n" para agregar una nueva línea
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
}


//Pre: -
//Post: -
void MapCreator::save_values(Tile& selectedTile, int& width_texture, int& window_width, int& window_height, SDL_Event& event){

    double newX = event.button.x;
    double newY = event.button.y;
                        
    // Me aseguro de que newX está por fuera de la imagen del asset y dentro de la ventana en X.
    double minX = width_texture;
    double maxX = window_width;
    if (newX < minX || newX > maxX)
        return;

    // Me aseguro de que newY está dentro de la ventana en Y
    double minY = window_height;
    double maxY = 0;
    if (newY < maxY || newY > minY)
        return;

    int multiploX = std::floor(newX / TILE_MAP_CREATED) * TILE_MAP_CREATED;
    int multiploY = std::floor(newY / TILE_MAP_CREATED) * TILE_MAP_CREATED;

    std::tuple<int,int> posicion = std::make_tuple(multiploY, multiploX);
    selectedTile.destRect = { multiploX, multiploY, TILE_MAP_CREATED, TILE_MAP_CREATED };

    mapTiles[posicion] = selectedTile;
}

// Pre: -
// Post: -
void MapCreator::select_map() {

    std::string mapName;
    bool is_already_create = false;
    std::cout << "Por favor, ingresa el nombre del nuevo mapa: ";
    std::cin >> mapName;

    if (mapName == "1") {
        mapName = "castle_earlong_mapa.csv";
    }

    if (std::ifstream(mapName)) {
        std::cout << "El mapa con el nombre '" << mapName << "' ya existe." << std::endl;

        std::string mapNameModified = mapName + "_modified";
        is_already_create = true;

        // Crear un nuevo archivo con el nombre modificado
        std::ofstream modifiedFile(mapNameModified);
        if (modifiedFile.is_open()) {
            // Copiar el contenido del archivo original al archivo modificado
            std::ifstream file(mapName);
            if (file.is_open()) {
                modifiedFile << file.rdbuf();
                file.close();
            } else {
                std::cerr << "No se pudo abrir el archivo original." << std::endl;
            }

            modify_map(modifiedFile, is_already_create);
        } else {
            std::cerr << "No se pudo crear el archivo modificado." << std::endl;
        }
    } else {
        std::cout << "El mapa: '" << mapName << "' no existe, se crea desde cero." << std::endl;
        std::ofstream file(mapName);
        if (file.is_open()) {
            create_map(file, is_already_create);
        } else {
            std::cerr << "No se pudo abrir el archivo y por lo tanto no se creó el mapa." << std::endl;
        }
    }
}


//Pre: -
//Post: -
void MapCreator::modify_map(std::ofstream& file, bool& is_already_create){

    SaveMapToCSV(file, is_already_create);
}


//Pre: -
//Post: -
void MapCreator::create_map(std::ofstream& file, bool& is_already_create){

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
    SDL_SetTextureBlendMode(assetTexture, SDL_BLENDMODE_BLEND);

    int window_width, window_height;
    SDL_GetRendererOutputSize(renderer, &window_width, &window_height);

    int width_texture, height_texture;
    SDL_QueryTexture(assetTexture, NULL, NULL, &width_texture, &height_texture);

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

                    save_values(selectedTile, width_texture, window_width, window_height, event);
                    mouseHeldDown = true;
                    break;
                }

                case SDL_MOUSEBUTTONUP: {
                    mouseHeldDown = false;
                    break;
                }

                case SDL_MOUSEMOTION: {

                    if(mouseHeldDown)
                        save_values(selectedTile, width_texture, window_width, window_height, event);
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

    SaveMapToCSV(file, is_already_create);
    
}