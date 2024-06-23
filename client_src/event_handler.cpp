#include "headers/event_handler.h"

// Pre: -
// Post: -
// cppcheck-suppress uninitMemberVar
EventHandler::EventHandler(ClientProtocol& protocol, bool& menu, bool& gameEnded, SoundManager& sound_manager): protocol(protocol), was_closed(false), in_menu(menu), gameEnded(gameEnded), sound_manager(sound_manager) {}

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
            break;
        case SDLK_LSHIFT:  // Suponiendo que SHIFT es el comando para correr
            cmd.action = Command::RUNFAST;
            break;
        case SDLK_f:
            cmd.action = Command::FIRE;
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
        case SDLK_ESCAPE:
            cmd.action = Command::NONE;
            in_menu = !in_menu;
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
    SDL_Event event;

    while (not was_closed) {
        SDL_WaitEvent(&event);

        switch (event.type) {
            case SDL_MOUSEBUTTONDOWN:
                if (gameEnded && event.button.button == SDL_BUTTON_LEFT) {
                    if (800/2 - 100 < event.button.x && event.button.x < 800/2 + 100
                     && 600/2 - 25 < event.button.y && event.button.y < 600/2+ 25) {
                        this->was_closed = true;
                    }
                }
                else if (in_menu && event.button.button == SDL_BUTTON_LEFT) {
                    if (800/4 + 800/4 - 70 < event.button.x && event.button.x < 800/4 + 800/4 + 70
                     && 600/4 + 600/4 - 15 < event.button.y && event.button.y < 600/4 + 600/4 + 15) {
                        sound_manager.change_music_volume();
                    }
                }
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
}

void EventHandler::close() { this->was_closed = true; }

void EventHandler::set_camara(Camara* c) { camara = c; }
