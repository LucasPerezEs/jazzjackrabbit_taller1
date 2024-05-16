
#include "headers/partida.h"

Partida::Partida(bool& server_closed): server_closed(server_closed) {}

// Pre:
// Post:
void Partida::run() {

    while (not server_closed) {

        /*
            Aca deberia de correr el juego. Es el game loop de una partida especifica.
        */


        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}
