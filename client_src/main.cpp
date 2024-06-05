#include <exception>
#include <fstream>
#include <iostream>

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

            Queue<Contenedor> receiverQueue;

            std::map<int, Entity*> entidades;
            std::map<int, Player*> personajes;

            Client client("localhost", "8080", receiverQueue, window, entidades, personajes);


            /*if(client.is_online()){

                setup.ShowMultiplayerMenu();


            }*/


            Game game(client, window, entidades, personajes);
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
