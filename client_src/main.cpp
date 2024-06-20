#include <exception>
#include <fstream>
#include <iostream>

#include "SDL2/SDL_mixer.h"
#include "SDL2/SDL_ttf.h"
#include "headers/SdlTexture.h"
#include "headers/UIManager.h"
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

            if (TTF_Init() < 0) {
                throw std::runtime_error(std::string("Error al iniciar TTF: ") + TTF_GetError());
            }

            if (SDL_Init(SDL_INIT_AUDIO) < 0) {
                throw std::runtime_error(std::string("Error al iniciar Audio subsystem: ") +
                                         SDL_GetError());
            }

            // TODO: Could configure some options
            // for our playback.
            if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
                throw std::runtime_error(std::string("Error al iniciar Audio subsystem: ") +
                                         Mix_GetError());
            }

            // Deberia enviarse ip y port (respectivamente);
            Client client("127.0.1", "8080");
            client.go_online();
            if (client.is_online()) {
                MultiplayerMenu multiplayerMenu;

                QObject::connect(&multiplayerMenu, &MultiplayerMenu::refreshRequested, [&]() {
                    std::vector<std::string> gameList;
                    if (client.refreshGameList(gameList)) {
                        multiplayerMenu.updateGameList(gameList);
                    }
                });

                QObject::connect(
                        &multiplayerMenu, &MultiplayerMenu::createGameRequested,
                        [&](const QString& gameID, const uint32_t& maxPlayers,
                            const std::vector<uint32_t>& cheats) {
                            if (client.createGame(gameID.toStdString(), maxPlayers, cheats)) {
                                multiplayerMenu.showGameCreatedMessage();
                            } else {
                                multiplayerMenu.showGameCreationFailedMessage();
                            }
                        });

                QObject::connect(&multiplayerMenu, &MultiplayerMenu::joinGameRequested,
                                 [&](const QString& gameID, const int& elegido) {
                                     if (client.joinGame(gameID.toStdString(), elegido)) {
                                         try {
                                             multiplayerMenu.exit = 0;
                                             multiplayerMenu.hide();
                                             Game game(client);
                                             std::cout << "Corriendo game\n";
                                             game.run();
                                             // multiplayerMenu.show();
                                         } catch (const std::exception& e) {
                                             std::cerr << "Exception during game run: " << e.what()
                                                       << std::endl;
                                         } catch (...) {
                                             std::cerr << "Unknown exception during game run."
                                                       << std::endl;
                                         }
                                     } else {
                                         multiplayerMenu.showJoinGameFailedMessage();
                                     }
                                 });

                QObject::connect(&multiplayerMenu, &MultiplayerMenu::createMapRequested, [&]() {
                    multiplayerMenu.close();

                    try {
                        Game game(client);
                        game.create_map();
                    } catch (const std::exception& e) {
                        std::cerr << "Exception during map creation: " << e.what() << std::endl;
                    } catch (...) {
                        std::cerr << "Unknown exception during map creation." << std::endl;
                    }
                });

                multiplayerMenu.exec();
                while (multiplayerMenu.exit == 0) {
                    multiplayerMenu.exit = 1;
                    multiplayerMenu.exec();
                }
            }
        }

        Mix_CloseAudio();
        TTF_Quit();
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
