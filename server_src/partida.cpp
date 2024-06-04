
#include "headers/partida.h"

Partida::Partida(bool& server_closed): server_closed(server_closed) {}

// Pre:
// Post:
void Partida::run() {
    /*Queue<Contenedor> q; // esta queue tiene que ir al sender
    Mapa m = Mapa();
    ListaObjetos objetos;
    std::vector<Ente*> entes;
    Personaje personaje = Personaje(4, 0, 2, 4, 100);
    Enemigo enemigo = Enemigo(50, 0, 2, 4, 100);
    objetos.agregar_objeto(&personaje);
    objetos.agregar_objeto(&enemigo);
    entes.push_back(&personaje);
    entes.push_back(&enemigo);*/


    while (not server_closed) {

        /*
            Aca deberia de correr el juego. Es el game loop de una partida especifica.
        */
        /*objetos.eliminar_borrados(q);
        objetos.correr_colisiones();
        for (auto e: entes) {
            e->update_vivo(objetos, q);
        }
        objetos.update(m, q);*/

        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}
