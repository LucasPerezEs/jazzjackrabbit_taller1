
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

        QApplication app(argc, argv);

        AppMenu appMenu;

        QObject::connect(&appMenu, &AppMenu::createMapRequested, [&](const QString& mapName, const int& widthMap,
                            const int& heightMap) {
            try {
                //appMenu.hide();
                MapCreator map(mapName.toStdString(), widthMap, heightMap, false);
                map.select_map();
            } catch (const std::exception& e) {
                std::cerr << "Exception during map creation: " << e.what() << std::endl;
            } catch (...) {
                std::cerr << "Unknown exception during map creation." << std::endl;
            }
        });

        QObject::connect(&appMenu, &AppMenu::modifyMapRequested, [&](const QString& mapName) {
            try {
                MapCreator map(mapName.toStdString(), -1, -1, true);
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