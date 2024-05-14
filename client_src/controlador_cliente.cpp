#include "controlador_cliente.h"

// Pre: -
// Post: -
ControladorCliente::ControladorCliente(const std::string& hostname, const std::string& servname):
        protocolo(hostname, servname) {}

void ControladorCliente::handle_keydown(Player& player, const SDL_Event& event, Command& cmd) {
    const SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&)event;
    switch (keyEvent.keysym.sym) {
        case SDLK_w:
            // std::cout << "Estoy subiendo" << std::endl;
            cmd.action = Command::UP;
            break;
        case SDLK_s:
            cmd.action = Command::DOWN;
            // std::cout << "Estoy bajando" << std::endl;
            break;
        case SDLK_a:
            cmd.action = Command::LEFT;
            player.moveLeft();
            // std::cout << "Voy a la izquierda" << std::endl;
            break;
        case SDLK_d:
            cmd.action = Command::RIGHT;
            player.moveRigth();
            break;
        case SDLK_SPACE:
            cmd.action = Command::JUMP;
            // std::cout << "Estoy saltando" << std::endl;
            break;
        case SDLK_LSHIFT:  // Suponiendo que SHIFT es el comando para correr
            cmd.action = Command::RUN;
            // std::cout << "Estoy corriendo" << std::endl;
            break;
    }
}

void ControladorCliente::handle_keyup(Player& player, const SDL_Event& event) {
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

// Pre: -
// Post: Se momemento los controles son: W, S, A, D, barra espaciadora y shift.
bool ControladorCliente::handle_events(Player& player) {

    Command cmd;
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_KEYDOWN:
                this->handle_keydown(player, event, cmd);
                std::cout << "aprete a" << std::endl;
                this->protocolo.send_command(cmd);
                break;
            case SDL_KEYUP:
                this->handle_keyup(player, event);
                break;
            case SDL_QUIT:
                std::cout << "Quit :(" << std::endl;
                return false;
        }
    }
    return true;
}
