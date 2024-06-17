#include "headers/game.h"

int escala2x = 26;
int escala2y = 26;
std::unordered_map<int, SDL_Texture*> tileTextures;

Game::Game(Client& client, SdlWindow& window, std::map<int, Entity*>& entidades,
           std::map<int, Player*>& personajes, UIManager& ui_manager):
        client(client),
        window(window),
        entidades(entidades),
        personajes(personajes),
        ui_manager(ui_manager) {

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

    client.get_EventHandler()->set_camara(camara);
}

void Game::run() {

    uint32_t time1 = 0;
    time1 = SDL_GetTicks();

    client.go_online();

    Music musica("../client_src/assets/music/Its_Pizza_Time.wav");
    musica.PlayMusic(-1);
    musica.SetVolume(20);

    while (client.is_online()) {

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

    this->close();
}


/*
VERSION ANTERIOR
// Modifica SaveMapToCSV para guardar los IDs de los tiles
void Game::SaveMapToCSV(const std::vector<Tile>& tiles, const std::string& filename) {
    std::ofstream file(filename);

    int contador = 0;
    int contador_multiplo = 0;

    if (file.is_open()) {
        for (const auto& tile : tiles) {

            if(contador_multiplo == 80){
                file << tile.id << "," << "\n";
                contador++;
                contador_multiplo = 0;

            } else {
                file << tile.id << ",";
                contador++;
                contador_multiplo++;
            }
        }

        while((80*20) >= contador){

            if(contador_multiplo == 80){
                file << "-1" << "," << "\n";
                contador++;
                contador_multiplo = 0;

            } else {
                file << "-1" << ",";
                contador++;
                contador_multiplo++;
            }
        
        } 

        file.close();
    } else {
        std::cerr << "No se pudo abrir el archivo para guardar." << std::endl;
    }
}
*/

// Modifica SaveMapToCSV para guardar los IDs de los tiles
void Game::SaveMapToCSV(const std::vector<Tile>& tiles, const std::string& filename) {
    std::ofstream file(filename);
    int fila_anterior = -1;

    if (file.is_open()) {
        for (const auto& pair : mapTiles) {
            const std::tuple<int, int>& key = pair.first;
            const Tile& value = pair.second;
            int fila_actual = std::get<0>(key);

            if(fila_actual != fila_anterior) {
                if(fila_anterior != -1) {
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


/*
Hay dos formas en la que se hizo esto. La primera solo requiere el uso de los case: SDL_MOUSEBUTTONDOWN y case: SDL_MOUSEBUTTONUP,
en este caso no se ve como se arrastra cada cuadricula hacia su posicion.

De la otra forma en la que si se ve es con lo agregado en case: SDL_MOUSEMOTION, pero este metodo requiere de agregar fuera del switch un for que va
desde 0 a numTiles. Si se saca esta funcionalidad ese for deberia borrarse asi como tambien el this->window.fill(); que se realiza allí. 
*/
void Game::create_map(){

    SDL_Renderer* renderer = this->window.getRenderer();

    // Crear una cuadrícula de tiles (ejemplo: 10x10)
    std::vector<Tile> tiles_mapa;
    std::vector<Tile> tiles_asset;
    std::tuple<int, int> posicion; //Posicion en el mapa

    // Cargar la imagen de assets
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

    // Habilita el blending para transparencia
    SDL_SetTextureBlendMode(assetTexture, SDL_BLENDMODE_BLEND);

    // Obtengo las dimensiones de la ventana
    int window_width, window_height;
    SDL_GetRendererOutputSize(renderer, &window_width, &window_height);
    std::cout << "El ancho de la ventana es: " << window_width << " y el alto es: " << window_height << std::endl;

    //Obtengo el ancho y alto de la textura
    int width_texture, height_texture;
    SDL_QueryTexture(assetTexture, NULL, NULL, &width_texture, &height_texture);

    int numTiles = (width_texture / 16) * (height_texture / 16); //Numero total de tiles de 16x16 en el asset.
    int tilesPerRow = (width_texture / 16); //Cantidad de tiles de 16 x 16 en el asset.
    
    //Inicializo cada bloque de la paleta de tiles para dibujar (y los hagos de 16x16).
    for (int i = 0; i < numTiles; i++) {
        Tile tile;
        tile.id = i;
        tile.posicion = {{i % tilesPerRow}, {i / tilesPerRow}};
        tile.srcRect = {(i % tilesPerRow)*16, (i / tilesPerRow)*16, 16, 16};
        tile.selected = false;
        tiles_asset.push_back(tile);
    }
    SDL_Rect destRect = {0, 0, width_texture, height_texture};
    SDL_RenderCopy(renderer, assetTexture, NULL, &destRect);
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

                    // Verifica si se hizo clic en un tile de la imagen de assets
                    for (auto& tile : tiles_asset) {
                        if (SDL_PointInRect(&mousePos, &tile.srcRect)) {
                            selectedTile = tile;
                            selectedTile.selected = true;
                            break;
                        }
                    }

                    if(!selectedTile.selected)
                        break;

                    //Si ya hay uno seleccionado
                    double newX = event.button.x;
                    double newY = event.button.y;
                        
                    // Me aseguro de que newX está por fuera de la imagen del asset y dentro de la ventana en X.
                    double minX = width_texture;
                    double maxX = window_width;
                    if (newX < minX || newX > maxX)
                        break;

                    // Me aseguro de que newY está dentro de la ventana en Y
                    double minY = window_height;
                    double maxY = 0;
                    if (newY < maxY || newY > minY)
                        break;

                    //Esto es para que los bloques de las texturas se posiciones siempre en una posicion de 16x16 y no que puedas poner
                    //la mitad de un asset sobre la mitad de otro. Si no crear un mapa con esta herramienta es un quilombo.
                    int multiploX = std::floor(newX / 16) * 16;
                    int multiploY = std::floor(newY / 16) * 16;

                    posicion = std::make_tuple(multiploY, multiploX);
                    selectedTile.destRect = { multiploX, multiploY, 16, 16 };
                    tiles_mapa.push_back(selectedTile);

                    mapTiles[posicion] = selectedTile; //({posicion, selectedTile}); //Si uso este ya no necesito usar tiles_map (Creo)

                    mouseHeldDown = true;
                    break;
                }

                case SDL_MOUSEBUTTONUP: {
                    
                    // Cuando se suelta el botón del ratón, reinicia la variable de estado
                    mouseHeldDown = false;
                    break;
                }

                case SDL_MOUSEMOTION: {
                    if(mouseHeldDown){
                        double newX = event.button.x;
                        double newY = event.button.y;
                        
                        // Me aseguro de que newX está por fuera de la imagen del asset y dentro de la ventana en X.
                        double minX = width_texture;
                        double maxX = window_width;
                        if (newX < minX || newX > maxX)
                            break;

                        // Me aseguro de que newY está dentro de la ventana en Y
                        double minY = window_height;
                        double maxY = 0;
                        
                        if (newY < maxY || newY > minY)
                            break;

                        //Esto es para que los bloques de las texturas se posiciones siempre en una posicion de 16x16 y no que puedas poner
                        //la mitad de un asset sobre la mitad de otro. Si no crear un mapa con esta herramienta es un quilombo.
                        int multiploX = std::floor(newX / 16) * 16;
                        int multiploY = std::floor(newY / 16) * 16;

                        posicion = std::make_tuple(multiploY, multiploX);
                        selectedTile.destRect = { multiploX, multiploY, 16, 16 };
                        tiles_mapa.push_back(selectedTile);

                        mapTiles.insert({posicion, selectedTile}); //Si uso este ya no necesito usar tiles_map (Creo)
                    }
                    break;
                }
                
            }
            this->window.fill();

            //Esto muestra los assets colocados durante la creacion del mapa (es el mapa creado visualmente)
            for(size_t i = 0; i < tiles_mapa.size(); i++)
                SDL_RenderCopy(renderer, assetTexture, &(tiles_mapa[i].srcRect), &(tiles_mapa[i].destRect));

            //Esto muestra el asset por pantalla (Es como la paleta de pinturas)
            for (int i = 0; i < numTiles; i++) {
                Tile tile;
                tile.id = i;
                tile.srcRect = {(i % tilesPerRow)*16, (i / tilesPerRow)*16, 16, 16};
                tile.selected = false;
                tiles_asset.push_back(tile);
                SDL_RenderCopy(renderer, assetTexture, &tile.srcRect, &tile.srcRect);
            }
            this->window.render();
        }
    }

    SaveMapToCSV(tiles_mapa, "Nuevo_mapa");
    this->close();
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

    Entity* entidad;
    if (personajes.find(client.get_id()) != personajes.end()) {
        entidad = static_cast<Entity*>(personajes[client.get_id()]);
    } else {
        if (personajes.size() > 0) {
            entidad = static_cast<Entity*>(personajes.begin()->second);
        } else {
            entidad = entidades.begin()->second;
        }
    }

    camara->actualizar_pos(entidad->getPosition().first, entidad->getPosition().second);

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

void Game::close() { client.close(); }



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
