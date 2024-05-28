#include "headers/game.h"

Game::Game(Client& client, SdlWindow& window, Player& player,
           std::vector<std::vector<float>>& objetos):
        client(client), window(window), player(player), objetos(objetos) {}

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

    for (auto o: objetos) {
        SDL_Rect r;
        r.h = ((o[2] - o[4]) * 6);
        r.w = ((o[3] - o[1]) * 8);
        r.x = o[1] * 8;
        r.y = 600 - (o[2] * 6);
        SDL_RenderDrawRect(window.getRenderer(), &r);
    }
    SDL_SetRenderDrawColor(window.getRenderer(), 0, 0, 0, 255);

    SDL_RenderPresent(window.getRenderer());
    /*this->window.fill();
    player.render();
    this->window.render();*/
}

void Game::close() { client.close(); }
