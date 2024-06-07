#include "headers/game.h"

int escala2x = 32;
int escala2y = 24;

Game::Game(Client& client, SdlWindow& window, std::map<int, Entity*>& entidades,
           std::map<int, Player*>& personajes):
        client(client),
        window(window),
        entidades(entidades),
        personajes(personajes),
        UI_manager(personajes, window) {

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
    
    camara = new Camara(0, 0, 800, 600, tilemap_terreno_solido[0].size(), tilemap_terreno_solido.size());
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

    UI_manager.render_UI(this->client.get_id());

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

    /*Entity* entidad;
    if (personajes.find(client.get_id()) != personajes.end()) {
        entidad = static_cast<Entity*>(personajes[client.get_id()]);
    } else {
        if (personajes.size() > 0) {
            entidad = static_cast<Entity*>(personajes.begin()->second);
        } else if (entidades.size() > 0) {
            entidad = entidades.begin()->second;
        } else {
            return;
        }
    }

    std::pair<float, float> posicion = entidad->getPosition();*/

    // Tamaño del tile en píxeles
    // int TILE_SIZE = 32;
    int TILESET_WIDTH = 20;

    // Tamaño de la ventana en píxeles
    //int WINDOW_WIDTH = 800;
    //int WINDOW_HEIGHT = 600;

    // Tamaño de la ventana en tiles
    // int WINDOW_WIDTH_TILES = WINDOW_WIDTH / TILE_SIZE;
    // int WINDOW_HEIGHT_TILES = WINDOW_HEIGHT / TILE_SIZE;

    // Posición de la cámara en tiles
    // int camX = posicion.first;
    // int camY = 40 - std::ceil(posicion.second);

    // Se asegura de que la cámara no se salga de los límites del mapa
    // camX = std::max(0, std::min(camX, static_cast<int>(tilemap[0].size()) - WINDOW_WIDTH_TILES));
    // camY = std::max(0, std::min(camY, static_cast<int>(tilemap.size()) - WINDOW_HEIGHT_TILES));

    // Ahora recorre solo los tiles que están dentro de la vista de la cámara
    for (int y = 0; y < 40; y++) {
        for (int x = 0; x < 80; x++) {

            // Calcula la posición del tile en el mapa
            // int tileX = std::min(camX + x, 80);
            // int tileY = std::min(camY + y, 40);

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
            destinationRect.x = (posX - camara->x)*camara->escalax;
            destinationRect.y = (camara->y - posY)*camara->escalay;
            destinationRect.w = camara->escalax;
            destinationRect.h = camara->escalay;

            // Renderiza el tile
            SDL_RenderCopy(this->window.getRenderer(), tilesetTexture, &sourceRect,
                           &destinationRect);
        }
    }
}

// tengo que hacer la camara y arreglar las fisicas para que se peguen al terreno
