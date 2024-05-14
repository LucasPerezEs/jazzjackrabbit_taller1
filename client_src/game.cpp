#include "game.h"

Game::Game(const std::string& hostname, const std::string& servname, Player& player,
           SdlWindow& window):
        controlador_cliente(hostname, servname), player(player), window(window) {}

void Game::run() {
    uint32_t time1 = 0;
    time1 = SDL_GetTicks();


    bool running = true;
    while (running) {

        running = this->controlador_cliente.handle_events(player);

        this->update(FRAME_RATE);

        this->render();

        uint32_t time2;
        time2 = SDL_GetTicks();
        uint32_t rest = FRAME_RATE - (time2 - time1);
        time1 = time2;

        usleep(rest);
    }
}

void Game::update(float dt) { this->player.update(dt); }

void Game::render() {
    this->window.fill();
    player.render();
    this->window.render();
}
