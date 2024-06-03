#include "headers/game.h"

Game::Game(Client& client, SdlWindow& window, Player& player, std::map<int, Entity*>& entidades):
        client(client), window(window), player(player), entidades(entidades) {}

void Game::run() {
    uint32_t time1 = 0;
    time1 = SDL_GetTicks();

    client.go_online();

    while (client.is_online()) {

        this->update();
        this->render();

        uint32_t time2;
        time2 = SDL_GetTicks();
        uint32_t rest = FRAME_RATE - (time2 - time1);
        time1 = time2;

        usleep(rest);
    }

    this->close();
}

void Game::update() {
    for (std::map<int, Entity*>::iterator it = entidades.begin(); it != entidades.end(); ++it) {
        it->second->update_animation();
    }
    /*if (entidades.count(0) > 0) {
        entidades[0]->update_animation();
    }
    if (entidades.count(1) > 0) {
        entidades[1]->update_animation();
    }*/
}

void Game::render() {
    this->window.fill();

    // Cuando esten todas las animaciones se pueden renderizar todas las entidades en partida

    //for (std::map<int, Entity*>::iterator it = entidades.begin(); it != entidades.end(); ++it) {
      //  it->second->render(window);
    //}
    /*if (entidades.count(0) > 0) {
        entidades[0]->render(window); // Renderizo solo el jugador para probar
    }
    if (entidades.count(1) > 0) {
        entidades[1]->render(window);
    }*/

    SDL_Surface* tilesetSurface = IMG_Load("../client_src/assets/background/medivo_map/TILESET_Medivo.png");
    if (tilesetSurface == nullptr) {
        std::cout << "Error al cargar la imagen: " << IMG_GetError() << std::endl;
        return;
    }

    SDL_Texture* tilesetTexture = SDL_CreateTextureFromSurface(this->window.getRenderer(), tilesetSurface);
    if (tilesetTexture == nullptr)
        std::cout << "Error al crear la textura: " << SDL_GetError() << std::endl;

    SDL_FreeSurface(tilesetSurface);

    //std::vector<std::vector<int>> tilemap_fondo = cargarCSV("../client_src/assets/background/medivo_map/Medivo_model_Fondo.csv");
    //draw(tilemap_fondo, tilesetTexture);

    std::vector<std::vector<int>> tilemap_terreno_solido = cargarCSV("../client_src/assets/background/medivo_map/Medivo_model_Terreno_completo.csv");
    draw(tilemap_terreno_solido, tilesetTexture);

    for (std::map<int, Entity*>::iterator it = entidades.begin(); it != entidades.end(); ++it) {
        it->second->render(window);
    }

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

void Game::draw(std::vector<std::vector<int>>& tilemap, SDL_Texture* tilesetTexture) {

     std::map<int, Entity*>::iterator it = entidades.begin();

    //int primer_clave = it->first;
    Entity* primer_valor = it->second;

    std::pair<float, float> posicion = primer_valor->getPosition();

    // Tamaño del tile en píxeles
    int TILE_SIZE = 32;
    int TILESET_WIDTH = 20;

    // Tamaño de la ventana en píxeles
    int WINDOW_WIDTH = 800;
    int WINDOW_HEIGHT = 600;

    // Tamaño de la ventana en tiles
    int WINDOW_WIDTH_TILES = WINDOW_WIDTH / TILE_SIZE;
    int WINDOW_HEIGHT_TILES = WINDOW_HEIGHT / TILE_SIZE;

    // Posición de la cámara en tiles
    int camX = posicion.first;
    int camY = 40 - std::ceil(posicion.second);

    // Se asegura de que la cámara no se salga de los límites del mapa
    camX = std::max(0, std::min(camX, static_cast<int>(tilemap[0].size()) - WINDOW_WIDTH_TILES));
    camY = std::max(0, std::min(camY, static_cast<int>(tilemap.size()) - WINDOW_HEIGHT_TILES));

    // Ahora recorre solo los tiles que están dentro de la vista de la cámara
    for (int y = 0; y < WINDOW_HEIGHT_TILES; y++){
        for (int x = 0; x < WINDOW_WIDTH_TILES; x++){

        // Calcula la posición del tile en el mapa
        int tileX = std::min(camX + x, 80);
        int tileY = std::min(camY + y, 40);

        // Obtiene el id del tile
        int tileValue = tilemap[tileY][tileX];

        // Calcula la posición del tile en píxeles
        int posX = x * TILE_SIZE;
        int posY = y * TILE_SIZE;

        SDL_Rect sourceRect;
        sourceRect.x = (tileValue % TILESET_WIDTH) * 16;
        sourceRect.y = (tileValue / TILESET_WIDTH) * 16;
        sourceRect.w = 16;
        sourceRect.h = 16;

        // Define el rectángulo de destino en la pantalla
        SDL_Rect destinationRect;
        destinationRect.x = posX;
        destinationRect.y = posY;
        destinationRect.w = TILE_SIZE;
        destinationRect.h = TILE_SIZE;

        // Renderiza el tile
        SDL_RenderCopy(this->window.getRenderer(), tilesetTexture, &sourceRect, &destinationRect);
    }
}
}
