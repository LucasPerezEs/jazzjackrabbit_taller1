#include "headers/game.h"

Game::Game(const std::string& hostname, const std::string& servname, SdlWindow& window):
        protocol(hostname, servname), event_handler(protocol), window(window), updater(protocol) {}

void Game::run() {
    uint32_t time1 = 0;
    time1 = SDL_GetTicks();

    // Atrapa los eventos de teclado/mouse del usuario y envia el mensaje adecuado al server
    this->event_handler.start();
    // Lee mensajes de la queue del server->cliente y actualiza los modelos
    this->updater.start();

    while (this->event_handler.is_running() and this->updater.is_running()) {

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

void Game::render() {
    this->window.fill();
    // player.render();
    this->window.render();
}

void Game::close() {
    this->protocol.stop();

    this->event_handler.close();
    this->event_handler.join();

    this->updater.close();
    this->updater.join();
}
