#include "headers/game.h"

Game::Game(Client& client, SdlWindow& window, Player& player, std::map<int, Entity*>& entidades):
        client(client), window(window), player(player), entidades(entidades) {}

void Game::run() {
    uint32_t time1 = 0;
    time1 = SDL_GetTicks();

    client.go_online();

    while (client.is_online()) {

        this->render();

        uint32_t time2;
        time2 = SDL_GetTicks();
        uint32_t rest = FRAME_RATE - (time2 - time1);
        time1 = time2;

        usleep(rest);
    }

    this->close();
}

void Game::update(float dt) { this->player.update(dt); }

void Game::render() {
    SDL_RenderClear(window.getRenderer());  // renderizo todo como un rectangulo

    SDL_SetRenderDrawColor(window.getRenderer(), 255, 255, 255, 255);

    for (std::map<int, Entity*>::iterator it = entidades.begin(); it != entidades.end(); ++it) {
        it->second->render(window);
    }
    SDL_SetRenderDrawColor(window.getRenderer(), 0, 0, 0, 255);

    SDL_RenderPresent(window.getRenderer());
    /*this->window.fill();
    player.render();
    this->window.render();*/
}

void Game::close() { client.close(); }
