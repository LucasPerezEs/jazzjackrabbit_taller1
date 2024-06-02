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

    // Tamaño de cada elemento del tilset.
    int tileWidth = 16;
    int tileHeight = 16;

    //Dimensiones de todo tileset.
    int tilset_width = 20; //Ancho del tile set (La imagen del tile set ocupa 320 pixeles de ancho pero como la divido en Tiles de 16x16 entonces 320/16= 20).

    int mapa_columns = 80;//tilemap.size(); Esto en realidad tambien es 80 ya que el CSV tiene 80
    int mapa_rows = 40;//tilemap[0].size();
    //int mapa_rows = 14;
    //int mapa_colums = 25;

    //std::cout << "Filas del CSV: " << mapa_rows << " y Columnas del CSV: " << mapa_colums << std::endl;

    int posicion_jugador_x = 0;
    int posicion_jugador_y = 20; 
    //No es por los anchos del tile set, es porque quiero que me muestra solo esto de alto en principio.
    //16 pixeles el lo que ocupa cada piso de alto, mas de eso se ve el piso superior.

    for (int x = posicion_jugador_x; x < mapa_columns; x++) {
        for (int y = posicion_jugador_y; y < mapa_rows; y++) {
    //for (int x = 0; x < mapa_colums; x++) {
      //  for (int y = 0; y < mapa_rows; y++) {

        //Obtienes el valor en la celda actual
        int tileValue = tilemap[y][x];

        //if(tileValue == -1)
          //  continue;

        // Calculas la posición del tile en el tileset
        SDL_Rect sourceRect;
        sourceRect.x = (tileValue % tilset_width) * tileWidth;
        sourceRect.y = (tileValue / tilset_width) * tileHeight;
        sourceRect.w = tileWidth;
        sourceRect.h = tileHeight;

        // Calculas la posición donde quieres renderizar el tile en la pantalla
        SDL_Rect destinationRect;
        destinationRect.x = (x - posicion_jugador_x) * 32;
        destinationRect.y = (y - posicion_jugador_y) * 32;
        destinationRect.w = 32;
        destinationRect.h = 32;

        //std::cout << "Fila: " << x << " y Columna: " << y << std::endl;
        //std::cout << "Soy el elemento: " << sourceRect.x << " - " << sourceRect.y << " de mi TileSet" << std::endl;

        // Renderizas el tile
        SDL_RenderCopy(this->window.getRenderer(), tilesetTexture, &sourceRect, &destinationRect);
        }
    }
}
