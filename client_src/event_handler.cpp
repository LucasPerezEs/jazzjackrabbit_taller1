#include "headers/event_handler.h"

// Pre: -
// Post: -
// cppcheck-suppress uninitMemberVar
EventHandler::EventHandler(ClientProtocol& protocol, bool& menu, bool& gameEnded, SoundManager& sound_manager, UIManager& uimanager):
    protocol(protocol), was_closed(false), in_menu(menu), gameEnded(gameEnded), sound_manager(sound_manager), uimanager(uimanager) {}

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
        case SDLK_o:
            if (event.key.repeat == 0) {
                cmd.action = Command::CHANGE_AMMO;
            }
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
        case SDLK_o:
            cmd.action = Command::NONE;
            break;
        default:
            cmd.action = Command::NONE;
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
                    if (uimanager.mainMenu.x < event.button.x && event.button.x < uimanager.mainMenu.x + uimanager.mainMenu.w
                     && uimanager.mainMenu.y < event.button.y && event.button.y < uimanager.mainMenu.y + uimanager.mainMenu.h) {
                        this->was_closed = true;
                    }
                }
                else if (in_menu && event.button.button == SDL_BUTTON_LEFT) {
                    if (uimanager.muteSound.x < event.button.x && event.button.x < uimanager.muteSound.x + uimanager.muteSound.w
                     && uimanager.muteSound.y < event.button.y && event.button.y < uimanager.muteSound.y + uimanager.muteSound.h) {
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
