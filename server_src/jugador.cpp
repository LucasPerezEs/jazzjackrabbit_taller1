#include "headers/jugador.h"

Jugador::Jugador(Socket&& socket, unsigned int& id_jugador, bool& server_closed):
        protocolo(std::move(socket)),
        id_jugador(id_jugador),
        jugador_online(true),
        server_closed(server_closed) {}

// Pre: -
// Post: -
bool Jugador::desconectar() {

    if (jugador_online) {
        protocolo.stop();
    }

    return jugador_online;
}

// Pre: -
// Post: -
void Jugador::run() {

    while (not server_closed) {
        std::cout << "Comando recibido: " << protocolo.receive_command() << std::endl;
        // Hago algo con el comando
    }

    jugador_online = false;
}
