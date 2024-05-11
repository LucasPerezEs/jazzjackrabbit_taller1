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

        //controlador.cargar_partida();
        controlador.jugar();

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
