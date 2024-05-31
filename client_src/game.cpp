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

    for (std::map<int, Entity*>::iterator it = entidades.begin(); it != entidades.end(); ++it) {
        it->second->render(window);
    }
    /*if (entidades.count(0) > 0) {
        entidades[0]->render(window); // Renderizo solo el jugador para probar
    }
    if (entidades.count(1) > 0) {
        entidades[1]->render(window);
    }*/

    this->window.render();
}

void Game::close() { client.close(); }
