#include "headers/game.h"

int escala2x = 26;
int escala2y = 26;

Game::Game(Client& client):
        client(client),
        window(800, 600),
        ui_manager(personajes, window), 
        client_receiver(client.get_protocol(), receiverQueue),
        in_menu(false),
        sound_manager(client.get_id()),
        event_handler(client.get_protocol(), in_menu, sound_manager),
        updater(client.get_protocol(), window, entidades, receiverQueue, personajes, ui_manager, client.get_id(), sound_manager) {

    SDL_Surface* tilesetSurface =
            IMG_Load("../client_src/assets/background/ASSETS_GENERALES.png");
    if (tilesetSurface == nullptr) {
        std::cout << "Error al cargar la imagen: " << IMG_GetError() << std::endl;
        return;
    }

    tilesetTexture = SDL_CreateTextureFromSurface(this->window.getRenderer(), tilesetSurface);
    if (tilesetTexture == nullptr)
        std::cout << "Error al crear la textura: " << SDL_GetError() << std::endl;

    SDL_FreeSurface(tilesetSurface);

    tilemap_terreno_solido = cargarCSV(
            "../client_src/assets/background/castle_erlong_map/castle_earlong_mapa.csv");

    // cppcheck-suppress noOperatorEq
    camara = new Camara(0, 0, 800, 600, tilemap_terreno_solido[0].size(),
                        tilemap_terreno_solido.size());

    event_handler.set_camara(camara);
}

void Game::run() {

    this->event_handler.start();
    this->updater.start();
    this->client_receiver.start();
    uint32_t time1 = 0;
    time1 = SDL_GetTicks();

    client.go_online();

    std::cout << "Iniciando musica\n";
    sound_manager.play_music();
    /*Music musica("../client_src/assets/music/Its_Pizza_Time.wav");
    musica.PlayMusic(-1);
    musica.SetVolume(20);*/

    while (updater.is_running()) {


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

    if (in_menu) {
        SDL_Rect background;
        background.x = 800/4;
        background.w = 800*2/4;
        background.y = 600/4;
        background.h = 600*2/4;
        SDL_SetRenderDrawColor(window.getRenderer(), 70, 130, 180, 255);
        SDL_RenderFillRect(window.getRenderer(), &background);

        SDL_Rect button;
        button.x = 800/4 + 800/4 - 70;
        button.w = 140;
        button.y = 600/4 + 600/4 - 15;
        button.h = 30;
        SDL_SetRenderDrawColor(window.getRenderer(), 255, 255, 255, 255);
        SDL_RenderFillRect(window.getRenderer(), &button);
    }

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

    int TILESET_WIDTH = 10;

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