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

    std::vector<std::vector<int>> tilemap_terreno = cargarCSV("../client_src/assets/background/medivo_map/mediva_map_csv.csv");
    draw(tilemap_terreno, tilesetTexture);

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

    // Tamaño de cada elemento del tilset.
    int tileWidth = 16;
    int tileHeight = 16;

    //Dimensiones de todo tileset.
    int tilset_width = 20;

    //int mapa_rows = tilemap.size();
    //int mapa_colums = tilemap[0].size();
    int mapa_rows = 14;
    int mapa_colums = 25;

    //std::cout << "Filas del CSV: " << mapa_rows << " y Columnas del CSV: " << mapa_colums << std::endl;

    //for (int x = 0; x < mapa_colums; x++) {
    //    for (int y = 0; y < mapa_rows; y++) {
    for (int x = 0; x < mapa_colums; x++) {
        for (int y = 0; y < mapa_rows; y++) {

        //Obtienes el valor en la celda actual
        int tileValue = tilemap[y][x];

        // Calculas la posición del tile en el tileset
        SDL_Rect sourceRect;
        sourceRect.x = (tileValue % tilset_width) * tileWidth;
        sourceRect.y = (tileValue / tileHeight) * tileHeight;
        sourceRect.w = tileWidth;
        sourceRect.h = tileHeight;

        // Calculas la posición donde quieres renderizar el tile en la pantalla
        SDL_Rect destinationRect;
        destinationRect.x = x * 48;
        destinationRect.y = y * 48;
        destinationRect.w = 48;
        destinationRect.h = 48;

        //std::cout << "Fila: " << x << " y Columna: " << y << std::endl;
        //std::cout << "Soy el elemento: " << sourceRect.x << " - " << sourceRect.y << " de mi TileSet" << std::endl;

        // Renderizas el tile
        SDL_RenderCopy(this->window.getRenderer(), tilesetTexture, &sourceRect, &destinationRect);
        }
    }
}
