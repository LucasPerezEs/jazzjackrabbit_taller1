#include <exception>
#include <fstream>
#include <iostream>



#include "setupscreen/MenuDialog.h"

#include "headers/SdlTexture.h"
#include "headers/entity.h"
#include "headers/game.h"

int main(int argc, char* argv[]) {
    try {

        QApplication app(argc, argv);

        MenuDialog menu;
        if (menu.exec() != QDialog::Accepted) {
            return -1; // El usuario canceló, salimos
        }

        std::string ip = menu.getIp().toStdString();
        std::string port = std::to_string(menu.getPort());


        SdlWindow window(800, 600);
        SdlTexture player_png("../client_src/assets/jazz_walking.png", window,
                              Color{0x2C, 0x66, 0x96});

        Player player(player_png);

        Queue<Contenedor> receiverQueue;

        std::map<int, Entity*> entidades;
        std::vector<std::vector<float>> objetos;

        Client client(ip, port, player, receiverQueue, window, entidades);

        Game game(client, window, player, entidades);
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
