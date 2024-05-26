#include "headers/event_handler.h"

// Pre: -
// Post: -
EventHandler::EventHandler(ClientProtocol& protocol,Player& player): protocol(protocol), player(player),was_closed(false) {}

void EventHandler::handle_keydown(const SDL_Event& event, Command& cmd) {
    const SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&)event;
    switch (keyEvent.keysym.sym) {
        case SDLK_w:
            std::cout << "Estoy subiendo" << std::endl;
            cmd.action = Command::UP;
            break;
        case SDLK_s:
            cmd.action = Command::DOWN;
            std::cout << "Estoy bajando" << std::endl;
            break;
        case SDLK_a:
            cmd.action = Command::LEFT;
            player.moveLeft();
            std::cout << "Voy a la izquierda" << std::endl;
            break;
        case SDLK_d:
            cmd.action = Command::RIGHT;
            std::cout << "Voy a la derecha" << std::endl;
            player.moveRigth();
            break;
        case SDLK_SPACE:
            cmd.action = Command::JUMP;
            std::cout << "Estoy saltando" << std::endl;
            break;
        case SDLK_LSHIFT:  // Suponiendo que SHIFT es el comando para correr
            cmd.action = Command::RUN;
            std::cout << "Estoy corriendo" << std::endl;
            break;
        default:  // Para el caso que toque una tecla no asignada.
            cmd.action = Command::NONE;
            break;
    }
}

void EventHandler::handle_keyup(const SDL_Event& event) {
    const SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&)event;
    switch (keyEvent.keysym.sym) {
        case SDLK_a:
            player.stopMoving();
            break;
        case SDLK_d:
            player.stopMoving();
            break;
    }
}

bool EventHandler::is_running() { return not was_closed; }

// Pre: -
// Post: Se momemento los controles son: W, S, A, D, barra espaciadora y shift.
void EventHandler::run() {

    Command cmd;
    SDL_Event event;

    while (not was_closed) {
        SDL_WaitEvent(&event);

        switch (event.type) {
            case SDL_KEYDOWN:
                this->handle_keydown(event, cmd);
                this->protocol.send_command(cmd);
                break;
            case SDL_KEYUP:
                this->handle_keyup(event);
                break;
            case SDL_QUIT:
                std::cout << "Quit :(" << std::endl;
                this->was_closed = true;
        }
    }
}

void EventHandler::close() { this->was_closed = true; }
