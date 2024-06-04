#include "headers/event_handler.h"

// Pre: -
// Post: -
EventHandler::EventHandler(ClientProtocol& protocol): protocol(protocol), was_closed(false) {}

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
                this->handle_keyup(event, cmd);
                this->protocol.send_command(cmd);
                break;
            case SDL_QUIT:
                std::cout << "Quit :(" << std::endl;
                cmd.action = Command::QUIT;
                this->protocol.send_command(cmd);
                this->was_closed = true;
        }
    }
}

void EventHandler::close() { this->was_closed = true; }
