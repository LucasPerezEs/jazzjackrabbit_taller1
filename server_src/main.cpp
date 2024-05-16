#include <exception>
#include <iostream>

#include "headers/game.h"

int main(int argc, char* argv[]) {
    try {
        int ret = -1;

        if (argc != 2) {
            std::cerr << "Bad program call. Expected " << argv[0] << " <servname>\n";
            return ret;
        }

        Game juego(argv[1]);
        juego.init_game();

        ret = 0;
        return ret;
    } catch (const std::exception& err) {
        std::cerr << "Something went wrong and an exception was caught: " << err.what() << "\n";
        return -1;
    } catch (...) {
        std::cerr << "Something went wrong and an unknown exception was caught.\n";
        return -1;
    }
}
