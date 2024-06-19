#include "headers/game.h"

int escala2x = 26;
int escala2y = 26;

Game::Game(Client& client):
        client(client),
        window(800, 600),
        ui_manager(personajes, window), 
        client_receiver(client.get_protocol(), receiverQueue),
        event_handler(client.get_protocol()),
        updater(client.get_protocol(), window, entidades, receiverQueue, personajes, ui_manager, client.get_id()) {

    SDL_Surface* tilesetSurface =
            IMG_Load("../client_src/assets/background/medivo_map/TILESET_Medivo.png");
    if (tilesetSurface == nullptr) {
        std::cout << "Error al cargar la imagen: " << IMG_GetError() << std::endl;
        return;
    }

    tilesetTexture = SDL_CreateTextureFromSurface(this->window.getRenderer(), tilesetSurface);
    if (tilesetTexture == nullptr)
        std::cout << "Error al crear la textura: " << SDL_GetError() << std::endl;

    SDL_FreeSurface(tilesetSurface);

    tilemap_terreno_solido = cargarCSV(
            "../client_src/assets/background/medivo_map/Medivo_model_Terreno_completo.csv");

    // cppcheck-suppress noOperatorEq
    camara = new Camara(0, 0, 800, 600, tilemap_terreno_solido[0].size(),
                        tilemap_terreno_solido.size());

    event_handler.set_camara(camara);
}

void Game::run() {

    this->event_handler.start();
    this->updater.start();
    this->client_receiver.start();
    std::cout << "Iniciados los threads\n";
    uint32_t time1 = 0;
    time1 = SDL_GetTicks();

    client.go_online();
    std::cout << "Iniciando musica\n";
    Music musica("../client_src/assets/music/Its_Pizza_Time.wav");
    musica.PlayMusic(-1);
    musica.SetVolume(20);
    std::cout << "Entrando al game loop\n";
    while (updater.is_running()) {
        std::cout << "Estoy en el loop del game\n";

        SDL_RenderClear(window.getRenderer());

        this->update();
        this->render();

        SDL_RenderPresent(window.getRenderer());

        uint32_t time2;
        time2 = SDL_GetTicks();
        uint32_t rest = FRAME_RATE - (time2 - time1);
        time1 = time2;

        usleep(rest);
    }
    std::cout << "Saliendo del game\n";
}






// Modifica SaveMapToCSV para guardar los IDs de los tiles
void Game::SaveMapToCSV(const std::string& filename) {
    std::ofstream file(filename);
    // cppcheck-suppress variableScope
    int fila_anterior = -1;

    if (file.is_open()) {
        for (const auto& pair: mapTiles) {
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
        std::cerr << "No se pudo abrir el archivo y por lo tanto no se creo el mapa." << std::endl;
    }
}

//Pre: -
//Post: -
void Game::save_values(Tile& selectedTile, int& width_texture, int& window_width, int& window_height, SDL_Event& event){

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

//Pre: -
//Post: -
void Game::create_map(){

    std::vector<Tile> tiles_asset;
    std::tuple<int, int> posicion;
    SDL_Renderer* renderer = this->window.getRenderer();


    SDL_Surface* tilesetSurface =
            IMG_Load("../client_src/assets/background/medivo_map/ASSETS_MEDIVO.png");
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
    std::cout << "El ancho de la ventana es: " << window_width << " y el alto es: " << window_height
              << std::endl;

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

                    if(mouseHeldDown){
                        save_values(selectedTile, width_texture, window_width, window_height, event);
                    }
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
    SaveMapToCSV("Nuevo_mapa");
}


void Game::update() {
    for (std::map<int, Entity*>::iterator it = entidades.begin(); it != entidades.end(); ++it) {
        it->second->update_animation();
    }

    for (std::map<int, Player*>::iterator it = personajes.begin(); it != personajes.end(); ++it) {
        it->second->update_animation();
    }
}

void Game::render() {
    this->window.fill();

    Entity* entidad = NULL;
    if (personajes.find(client.get_id()) != personajes.end()) {
        entidad = static_cast<Entity*>(personajes[client.get_id()]);
    } else {
        if (personajes.size() > 0) {
            entidad = static_cast<Entity*>(personajes.begin()->second);
        } else if (entidades.size() > 0) {
            entidad = entidades.begin()->second;
        }
    }

    if (entidad != NULL) {
        camara->actualizar_pos(entidad->getPosition().first, entidad->getPosition().second);
    } else {
        camara->actualizar_pos(0, 0);
    }
    

    draw(tilemap_terreno_solido, tilesetTexture);

    for (std::map<int, Entity*>::iterator it = entidades.begin(); it != entidades.end(); ++it) {
        it->second->render(window, entidad, camara);
    }

    for (std::map<int, Player*>::iterator it = personajes.begin(); it != personajes.end(); ++it) {
        it->second->render(window, entidad, camara);
    }

    ui_manager.render_UI(this->client.get_id());

    this->window.render();
}

Game::~Game() {

    //client.close();
    this->event_handler.close();
    this->event_handler.join();
    std::cout << "Haciendo join del event handler\n";
    //this->client_receiver.close();
    this->client_receiver.join();
    std::cout << "Haciendo join del receiver\n";
    this->updater.join();
    std::cout << "Haciendo join del updater\n";
}


std::vector<std::vector<int>> Game::cargarCSV(const std::string& ruta) {
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

void Game::draw(const std::vector<std::vector<int>>& tilemap, SDL_Texture* tilesetTexture) {

    int TILESET_WIDTH = 20;

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
            SDL_RenderCopy(this->window.getRenderer(), tilesetTexture, &sourceRect,
                           &destinationRect);
        }
    }
}

// tengo que hacer la camara y arreglar las fisicas para que se peguen al terreno
