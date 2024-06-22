
#include <exception>
#include <fstream>
#include <iostream>
#include <thread>
#include <stdexcept>

#include "SDL2/SDL_ttf.h"
#include "headers/SdlTexture.h"
#include "headers/map_creator.h"
#include "setupscreen_editor/SetupScreen.h"

int main(int argc, char* argv[]) {

    try {

        //SDL_Init(SDL_INIT_EVERYTHING);

        // Inicialización de la aplicación Qt
        QApplication app(argc, argv);

        AppMenu appMenu;

        QObject::connect(&appMenu, &AppMenu::createMapRequested, [&] {
            //appMenu.close();

            try {
                MapCreator map;
                map.select_map();
            } catch (const std::exception& e) {
                std::cerr << "Exception during map creation: " << e.what() << std::endl;
            } catch (...) {
                std::cerr << "Unknown exception during map creation." << std::endl;
            }
        });
        appMenu.exec();

    } catch (const std::exception& err) {
        std::cerr << "Something went wrong and an exception was caught: " << err.what() << "\n";
        return -1;
    } catch (...) {
        std::cerr << "Something went wrong and an unknown exception was caught.\n";
        return -1;
    }

    SDL_Quit();
}