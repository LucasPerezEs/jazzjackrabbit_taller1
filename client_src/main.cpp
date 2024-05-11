#include <exception>
#include <fstream>
#include <iostream>
#include <SDL.h>
#include "controlador_cliente.h"

int main(int argc, char* argv[]) {
    try {
        if (argc != 3 && argc != 4) {
            std::cerr << "Bad program call. Expected " << argv[0]
                      << " <hostname> <servername> [<filename>]\n";
            return -1;
        }

        ControladorCliente controlador(argv[1], argv[2]);

        SDL_Init(SDL_INIT_VIDEO); // Inicializa SDL2

        // Crea una ventana de aplicación
        SDL_Window* window = SDL_CreateWindow("Captura de teclas", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);

        // El bucle del juego
        bool cliente_activo = true;
        SDL_Event event;
        while (cliente_activo) {
            while (SDL_PollEvent(&event)) {

                if (event.type == SDL_QUIT) {
                    cliente_activo = false;
                    break;

                } else if (event.type == SDL_KEYDOWN) {
                    char cmd;
                    switch (event.key.keysym.sym) {
                        case SDLK_UP:
                            cmd = 'w'; // Suponiendo que 'w' es el comando para mover hacia arriba
                            break;
                        case SDLK_DOWN:
                            cmd = 's'; // Suponiendo que 's' es el comando para mover hacia abajo
                            break;
                        case SDLK_LEFT:
                            cmd = 'a'; // Suponiendo que 'a' es el comando para mover hacia la izquierda
                            break;
                        case SDLK_RIGHT:
                            cmd = 'd'; // Suponiendo que 'd' es el comando para mover hacia la derecha
                            break;
                        case SDLK_SPACE:
                            cmd = ' '; // Suponiendo que ' ' es el comando para saltar
                            break;
                        case SDLK_LSHIFT: // Suponiendo que SHIFT es el comando para correr
                            cmd = 'r';
                            break;
                }
                cliente_activo = controlador.ejecutar_comando(cmd);
            }
        }
    }

    // Limpia y cierra
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;

    } catch (const std::exception& err) {
        std::cerr << "Something went wrong and an exception was caught: " << err.what() << "\n";
        return -1;
    } catch (...) {
        std::cerr << "Something went wrong and an unknown exception was caught.\n";
        return -1;
    }
}
