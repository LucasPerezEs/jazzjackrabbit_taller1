#include <exception>
#include <fstream>
#include <iostream>

#include "headers/SdlTexture.h"
#include "headers/entity.h"
#include "headers/game.h"
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
            SdlTexture player_png("../client_src/assets/jazz_walking.png", window,
                                  Color{0x2C, 0x66, 0x96});

            Player player(player_png);

            Queue<Contenedor> receiverQueue;

            std::map<int, Entity*> entidades;
            std::vector<std::vector<float>> objetos;

            Client client(ip, port, player, receiverQueue, window, entidades);


            if(client.is_online()){

                setup.ShowMultiplayerMenu();


            }


            Game game(client, window, player, entidades);
            game.run();
        }


        return 0;

    } catch (const std::exception& err) {
        std::cerr << "Something went wrong and an exception was caught: " << err.what() << "\n";
        return -1;
    } catch (...) {
        std::cerr << "Something went wrong and an unknown exception was caught.\n";
        return -1;
    }
}
