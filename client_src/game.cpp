#include "headers/game.h"

int escala2x = 16;
int escala2y = 12;

Game::Game(Client& client, SdlWindow& window, Player& player, std::map<int, Entity*>& entidades):
        client(client), window(window), player(player), entidades(entidades) {

    SDL_Surface* tilesetSurface = IMG_Load("../client_src/assets/background/medivo_map/TILESET_Medivo.png");
    if (tilesetSurface == nullptr) {
        std::cout << "Error al cargar la imagen: " << IMG_GetError() << std::endl;
        return;
    }

    tilesetTexture = SDL_CreateTextureFromSurface(this->window.getRenderer(), tilesetSurface);
    if (tilesetTexture == nullptr)
        std::cout << "Error al crear la textura: " << SDL_GetError() << std::endl;

    SDL_FreeSurface(tilesetSurface);

    tilemap_terreno_solido = cargarCSV("../client_src/assets/background/medivo_map/Medivo_model_Terreno_completo.csv");
}

void Game::run() {
    uint32_t time1 = 0;
    time1 = SDL_GetTicks();

    client.go_online();

    while (client.is_online()) {

        //SDL_SetRenderDrawColor(window.getRenderer(), 0, 0, 0, 255);

        SDL_RenderClear(window.getRenderer());  // renderizo todo como un rectangulo

        //SDL_SetRenderDrawColor(window.getRenderer(), 255, 255, 255, 255);

        this->update();
        this->render();
        /*for (std::vector<int>::size_type i = tilemap_terreno_solido.size()-1; i >= 1; --i) {
            for (std::vector<int>::size_type j = 0; j < tilemap_terreno_solido[i].size(); j++) {
                if (tilemap_terreno_solido[i][j] != -1) {
                    // Asume que el tamaño de cada tile es de 32x32
                    SDL_Rect r;
                    r.h = ((1) * escala2y);
                    r.w = ((1) * escala2x);
                    r.x = j*2 * escala2x;
                    r.y = 600 - ((39-i)*2 * escala2y);
                    SDL_RenderDrawRect(window.getRenderer(), &r);

                    //std::cout << "Soy un piso y mi x1 es: " << piso->x << " mi x2 es: " << piso->w << " mi y1 es: " << piso->y << " mi y2 es: " << piso->h << std::endl;
                }
            }
        }*/

        SDL_RenderPresent(window.getRenderer());

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



    //std::vector<std::vector<int>> tilemap_fondo = cargarCSV("../client_src/assets/background/medivo_map/Medivo_model_Fondo.csv");
    //draw(tilemap_fondo, tilesetTexture);

    draw(tilemap_terreno_solido, tilesetTexture);

    for (std::map<int, Entity*>::iterator it = entidades.begin(); it != entidades.end(); ++it) {
        it->second->render(window, entidades.begin()->second);
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
    //int TILE_SIZE = 32;
    int TILESET_WIDTH = 20;

    // Tamaño de la ventana en píxeles
    int WINDOW_WIDTH = 800;
    int WINDOW_HEIGHT = 600;

    // Tamaño de la ventana en tiles
    //int WINDOW_WIDTH_TILES = WINDOW_WIDTH / TILE_SIZE;
    //int WINDOW_HEIGHT_TILES = WINDOW_HEIGHT / TILE_SIZE;

    // Posición de la cámara en tiles
    //int camX = posicion.first;
    //int camY = 40 - std::ceil(posicion.second);

    // Se asegura de que la cámara no se salga de los límites del mapa
    //camX = std::max(0, std::min(camX, static_cast<int>(tilemap[0].size()) - WINDOW_WIDTH_TILES));
    //camY = std::max(0, std::min(camY, static_cast<int>(tilemap.size()) - WINDOW_HEIGHT_TILES));

    // Ahora recorre solo los tiles que están dentro de la vista de la cámara
    for (int y = 0; y < 40; y++){
        for (int x = 0; x < 80; x++){

        // Calcula la posición del tile en el mapa
        //int tileX = std::min(camX + x, 80);
        //int tileY = std::min(camY + y, 40);

        // Obtiene el id del tile
        int tileValue = tilemap[y][x];

        // Calcula la posición del tile en píxeles
        int posX = x;
        int posY = y;

        SDL_Rect sourceRect;
        sourceRect.x = (tileValue % TILESET_WIDTH) * 16;
        sourceRect.y = (tileValue / TILESET_WIDTH) * 16;
        sourceRect.w = 16;
        sourceRect.h = 16;

        // Define el rectángulo de destino en la pantalla
        SDL_Rect destinationRect;
        destinationRect.x = 2*(posX)*escala2x-posicion.first*escala2x + WINDOW_WIDTH/2;
        //destinationRect.y = 2*(posY)*escala2y-(2*escala2y*tilemap.size()-WINDOW_HEIGHT)+ posicion.second*escala2y - 2*escala2y;  //Version1
        //destinationRect.y = 2*(posY)*escala2y + posicion.second*escala2y - WINDOW_HEIGHT/2; //Version2 que lo manejaba bien pero estaba desfasado.
        destinationRect.y = 2*(posY)*escala2y + posicion.second*escala2y - WINDOW_HEIGHT/2 - 80; //Version3 que arregla momentaneamente el desfase.


        destinationRect.w = 2*escala2x;
        destinationRect.h = 2*escala2y;
 
        // Renderiza el tile
        SDL_RenderCopy(this->window.getRenderer(), tilesetTexture, &sourceRect, &destinationRect);

    }
}
}
