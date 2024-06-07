#include <exception>
#include <fstream>
#include <iostream>

#include "SDL2/SDL_ttf.h"
#include "headers/SdlTexture.h"
#include "headers/entity.h"
#include "headers/game.h"
#include "headers/player.h"
#include "setupscreen/SetupScreen.h"

int main(int argc, char* argv[]) {
    try {

        QApplication app(argc, argv);

        SetupScreen setup;

        setup.ShowConnectMenu();

        if (setup.AcceptedConnection()) {
            std::string ip = setup.getIp().toStdString();
            std::string port = setup.getPort().toStdString();


            SdlWindow window(800, 600);

            if (TTF_Init() < 0) {
                std::cout << "Error al iniciar TTF: " << TTF_GetError() << std::endl;
            }

            Queue<Contenedor> receiverQueue;

            std::map<int, Entity*> entidades;
            std::map<int, Player*> personajes;

            Client client("localhost", "8080", receiverQueue, window, entidades, personajes);


            if(client.is_online()) {
                MultiplayerMenu multiplayerMenu;

                std::cout << "Refresh antes" << std::endl;
                QObject::connect(&multiplayerMenu, &MultiplayerMenu::refreshRequested, [&]() {
                    std::cout << "Refresh" << std::endl;
                    //auto gameList = client.refreshGameList();
                    //multiplayerMenu.updateGameList(gameList);
                });
                QObject::connect(&multiplayerMenu, &MultiplayerMenu::createGameRequested, [&]() {
                    if (client.createGame("Juego 1")) {

                    }
                    //   multiplayerMenu.showGameCreatedMessage();
                    //} else {
                    //  multiplayerMenu.showGameCreationFailedMessage();
                    // }
                });
                std::cout << "Join antes" << std::endl;
                QObject::connect(&multiplayerMenu, &MultiplayerMenu::joinGameRequested, [&](const QString &gameID) {
                    multiplayerMenu.close();
                    if (client.joinGame(gameID.toStdString())) {
                        Game game(client, window, entidades, personajes);
                        game.run();
                    }
                    //} else {
                    //  multiplayerMenu.showJoinGameFailedMessage();
                    //}
                });
                multiplayerMenu.show();
                multiplayerMenu.exec();

            }

            //Game game(client, window, entidades, personajes);
            //game.run();
        }

        TTF_Quit();
        return 0;

    } catch (const std::exception& err) {
        std::cerr << "Something went wrong and an exception was caught: " << err.what() << "\n";
        return -1;
    } catch (...) {
        std::cerr << "Something went wrong and an unknown exception was caught.\n";
        return -1;
    }
}
