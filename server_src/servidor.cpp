
#include "headers/servidor.h"

Servidor::Servidor(bool& juego_finalizado):
        server_closed(juego_finalizado), id_jugadores(0), partida(juego_finalizado) {}


void Servidor::add_player(Socket&& peer) {
    jugadores.emplace_back(std::move(peer), id_jugadores, server_closed);
    jugadores.back().run();
    id_jugadores++;
}

void Servidor::run() {
    // Toy corriendo el servidor.
}
