#include "headers/game.h"

Game::Game(const std::string& hostname, const std::string& servname, SdlWindow& window):
        event_handler(hostname, servname), window(window) {}

void Game::run() {
    uint32_t time1 = 0;
    time1 = SDL_GetTicks();

    // Atrapa los eventos de teclado/mouse del usuario y envia el mensaje adecuado al server
    this->event_handler.start();

    bool running = true;
    while (this->event_handler.is_running() and running) {

        // Cada etapa debe correr en un hilo separado, ya que son concurrentes.

        // Lee mensajes de la queue del server->cliente y actualiza los modelos
        this->update(FRAME_RATE);

        // Render de la pantalla con el modelo actual.
        this->render();

        // Pregunta: todas las partes del event loop (handle-events, update, render) deben correr a
        // un constant frame loop?
        //          o solo el renderizado de imagen?

        uint32_t time2;
        time2 = SDL_GetTicks();
        uint32_t rest = FRAME_RATE - (time2 - time1);
        time1 = time2;

        usleep(rest);
    }

    this->event_handler.join();
}

void Game::update(float dt) {
    // this->player.update(dt);
}

void Game::render() {
    this->window.fill();
    // player.render();
    this->window.render();
}
