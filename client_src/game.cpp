#include "headers/game.h"

Game::Game(Client& client, SdlWindow& window, Player& player):
        client(client), window(window), player(player) {}

void Game::run() {
    uint32_t time1 = 0;
    time1 = SDL_GetTicks();

    client.go_online();

    while (client.is_online()) {


        this->update(FRAME_RATE);
        // Render de la pantalla con el modelo actual.
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
    this->window.fill();
    player.render();
    this->window.render();
}

void Game::close() {
    client.close();
}
