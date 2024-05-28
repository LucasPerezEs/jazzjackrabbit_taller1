#include <exception>
#include <fstream>
#include <iostream>

#include <SDL.h>

#include "headers/SdlTexture.h"
#include "headers/game.h"

int main(int argc, char* argv[]) {
    try {
        if (argc != 3 && argc != 4) {
            std::cerr << "Bad program call. Expected " << argv[0]
                      << " <hostname> <servername> [<filename>]\n";
            return -1;
        }

        SdlWindow window(800, 600);
        SdlTexture player_png("../client_src/assets/jazz_walking.png", window,
                              Color{0x2C, 0x66, 0x96});

        Player player(player_png);

        Queue<Contenedor> receiverQueue;

        std::vector<std::vector<float>> objetos;

        Client client(argv[1], argv[2], player, receiverQueue, window, objetos);

        Game game(client, window, player, objetos);
        game.run();

        return 0;

    } catch (const std::exception& err) {
        std::cerr << "Something went wrong and an exception was caught: " << err.what() << "\n";
        return -1;
    } catch (...) {
        std::cerr << "Something went wrong and an unknown exception was caught.\n";
        return -1;
    }
}
