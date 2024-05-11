
#include "controlador_cliente.h"

// Pre: -
// Post: -
ControladorCliente::ControladorCliente(const std::string& hostname, const std::string& servname):
        protocolo(hostname, servname) {}


// Pre: -
// Post: Se momemento los controles son: W, S, A, D, barra espaciadora y shift.
void ControladorCliente::jugar() {

    Command cmd;
    SDL_Event event;
    bool cliente_conectado = true;

    while (cliente_conectado) {
        while (SDL_PollEvent(&event)) {

            if (event.type == SDL_QUIT) {
                cliente_conectado = false;
                break;

            } else if (event.type == SDL_KEYDOWN) {

                switch (event.key.keysym.sym) {
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
                        std::cout << "Voy a la izquierda" << std::endl;
                        break;
                    case SDLK_d:
                        cmd.action = Command::RIGHT;
                        std::cout << "Voy a la derecha" << std::endl;
                        break;
                    case SDLK_SPACE:
                        cmd.action = Command::JUMP;
                        std::cout << "Estoy saltando" << std::endl;
                        break;
                    case SDLK_LSHIFT: // Suponiendo que SHIFT es el comando para correr
                        cmd.action = Command::RUN;
                        std::cout << "Estoy corriendo" << std::endl;
                        break;
                }

                protocolo.send_command(cmd);
            }
        }
    }
}