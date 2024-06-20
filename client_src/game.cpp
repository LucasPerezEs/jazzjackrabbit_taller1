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

    //Este asset tambien deberia de pedirselo al map creator y que este le devuelva ya la textura.
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

    //Aca deberia ir un seleccionador de mapas pero todavia no se implementó (en proceso).
    MapCreator load_map(client);
    tilemap = load_map.cargarCSV(
            "../client_src/assets/background/castle_erlong_map/castle_earlong_mapa.csv");

    // cppcheck-suppress noOperatorEq
    camara = new Camara(0, 0, 800, 600, tilemap[0].size(),tilemap.size());

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
    
    Drawer drawer(this->window);
    drawer.draw_with_camara(tilemap, tilesetTexture, camara);

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

    this->event_handler.close();
    this->event_handler.join();
    std::cout << "Haciendo join del event handler\n";
    //this->client_receiver.close();
    this->client_receiver.join();
    std::cout << "Haciendo join del receiver\n";
    this->updater.join();
    std::cout << "Haciendo join del updater\n";
}