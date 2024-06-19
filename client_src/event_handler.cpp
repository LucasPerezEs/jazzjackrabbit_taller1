#include "headers/event_handler.h"

// Pre: -
// Post: -
EventHandler::EventHandler(ClientProtocol& protocol):
        protocol(protocol),
        was_closed(false),
        jump_effect("../client_src/assets/music/jump_sound.wav"),
        shot_effect("../client_src/assets/music/shot_sound.wav"),
        run_effect("../client_src/assets/music/run_sound.wav") {}

void EventHandler::handle_keydown(const SDL_Event& event, Command& cmd) {
    const SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&)event;

    switch (keyEvent.keysym.sym) {
        case SDLK_w:
            cmd.action = Command::UP;
            break;
        case SDLK_s:
            cmd.action = Command::DOWN;
            break;
        case SDLK_a:
            cmd.action = Command::LEFT;
            break;
        case SDLK_d:
            cmd.action = Command::RIGHT;
            break;
        case SDLK_SPACE:
            cmd.action = Command::JUMP;
            jump_effect.PlaySound();
            break;
        case SDLK_LSHIFT:  // Suponiendo que SHIFT es el comando para correr
            cmd.action = Command::RUNFAST;
            run_effect.PlaySound();
            break;
        case SDLK_f:
            cmd.action = Command::FIRE;
            shot_effect.PlaySound();
            break;
        case SDLK_k:
            cmd.action = Command::SPECIAL;
            break;
        case SDLK_UP:
            cmd.action = Command::NONE;
            camara->zoomIn();
            break;
        case SDLK_DOWN:
            cmd.action = Command::NONE;
            camara->zoomOut();
            break;
        default:  // Para el caso que toque una tecla no asignada.
            cmd.action = Command::NONE;
            break;
    }
}

void EventHandler::handle_keyup(const SDL_Event& event, Command& cmd) {
    const SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&)event;
    switch (keyEvent.keysym.sym) {
        case SDLK_a:
            cmd.action = Command::STOPLEFT;
            break;
        case SDLK_d:
            cmd.action = Command::STOPRIGHT;
            break;
        case SDLK_f:
            cmd.action = Command::STOPFIRE;
            break;
        case SDLK_LSHIFT:  // Suponiendo que SHIFT es el comando para correr
            cmd.action = Command::RUN;
            break;
    }
}

bool EventHandler::is_running() { return not was_closed; }

// Pre: -
// Post: Se momemento los controles son: W, S, A, D, barra espaciadora y shift.
void EventHandler::run() {
    std::cout << "Entrando al loop del event handler\n";
    SDL_Event event;

    jump_effect.SetupDevice();
    shot_effect.SetupDevice();
    run_effect.SetupDevice();
    while (not was_closed) {
        std::cout << "Estoy en el loop del event handler\n";
        SDL_WaitEvent(&event);

        switch (event.type) {
            case SDL_KEYDOWN: {
                Command cmd;
                this->handle_keydown(event, cmd);
                Message msg(cmd.action);
                this->protocol.send_message(msg);
                break;
            }
            case SDL_KEYUP: {
                Command cmd;
                this->handle_keyup(event, cmd);
                Message msg(cmd.action);
                this->protocol.send_message(msg);
                break;
            }
            case SDL_QUIT:
                std::cout << "Ha salido del juego" << std::endl;
                Message quitMessage(Command::QUIT);
                this->protocol.send_message(quitMessage);
                this->was_closed = true;
                break;
        }
    }
    std::cout << "Saliendo del event handler\n";
}

void EventHandler::close() { this->was_closed = true; }

void EventHandler::set_camara(Camara *c) {
    camara = c;
}
