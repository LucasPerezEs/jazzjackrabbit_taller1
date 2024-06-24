#include "headers/game.h"

int escala2x = 26;
int escala2y = 26;

Game::Game(Client& client):
        client(client),
        window(800, 600),
        ui_manager(personajes, window),
        client_receiver(client.get_protocol(), receiverQueue),
        gameStarted(false),
        gameEnded(false),
        in_menu(false),
        sound_manager(client.get_id()),
        event_handler(client.get_protocol(), in_menu, gameEnded, sound_manager, ui_manager),
        updater(client.get_protocol(), window, entidades, receiverQueue, personajes, ui_manager, client.get_id(), sound_manager, gameStarted, gameEnded) {

    // Este asset tambien deberia de pedirselo al map creator y que este le devuelva ya la textura.
    SDL_Surface* tilesetSurface = IMG_Load("../client_src/assets/background/ASSETS_GENERALES.png");
    if (tilesetSurface == nullptr) {
        std::cout << "Error al cargar la imagen: " << IMG_GetError() << std::endl;
        return;
    }

    tilesetTexture = SDL_CreateTextureFromSurface(this->window.getRenderer(), tilesetSurface);
    if (tilesetTexture == nullptr)
        std::cout << "Error al crear la textura: " << SDL_GetError() << std::endl;
    SDL_FreeSurface(tilesetSurface);

    SDL_Surface* loadingSurface = IMG_Load("../client_src/assets/loading/loading.png");
    if (loadingSurface == nullptr) {
        std::cout << "Error al cargar la imagen: " << IMG_GetError() << std::endl;
        return;
    }

    loadingImage = SDL_CreateTextureFromSurface(this->window.getRenderer(), loadingSurface);
    if (loadingImage == nullptr)
        std::cout << "Error al crear la textura: " << SDL_GetError() << std::endl;
    SDL_FreeSurface(loadingSurface);

    tilemap = client.getMap();

    // cppcheck-suppress noOperatorEq
    camara = new Camara(0, 0, 800, 600, tilemap[0].size(), tilemap.size());

    event_handler.set_camara(camara);
}

void Game::run() {

    this->event_handler.start();
    this->updater.start();
    this->client_receiver.start();
    uint32_t time1 = 0;
    time1 = SDL_GetTicks();

    client.go_online();


    // Si el client no tiene mapa(is empty) le pido que lo cargue.

    // std::cout << "Iniciando musica\n";
    /*Music musica("../client_src/assets/music/Its_Pizza_Time.wav");
    musica.PlayMusic(-1);
    musica.SetVolume(20);*/

    while (updater.is_running() && event_handler.is_running()) {

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
    sound_manager.stop_music();
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

    if (gameEnded) {
        ui_manager.renderEndGame(this->client.get_id());
    }
    else if (!gameStarted) {
        SDL_RenderCopy(window.getRenderer(), loadingImage, NULL, NULL);
        ui_manager.renderLoadingText();
    } else {

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

        Drawer drawer(this->window);
        drawer.draw_with_camara(tilemap, tilesetTexture, camara);

        for (std::map<int, Entity*>::iterator it = entidades.begin(); it != entidades.end(); ++it) {
            it->second->render(window, entidad, camara);
        }

        for (std::map<int, Player*>::iterator it = personajes.begin(); it != personajes.end();
             ++it) {
            it->second->render(window, entidad, camara);
        }

        ui_manager.render_UI(this->client.get_id());

    if (in_menu) {
        ui_manager.renderPauseMenu();
    }

    this->window.render();
    }
}

Game::~Game() {

    this->event_handler.close();
    this->event_handler.join();
    std::cout << "Haciendo join del event handler\n";
    // this->client_receiver.close();
    this->client_receiver.join();
    std::cout << "Haciendo join del receiver\n";
    this->updater.close();
    this->updater.join();
    std::cout << "Haciendo join del updater\n";
}
