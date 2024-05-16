#include "headers/aceptador.h"

Aceptador::Aceptador(const std::string& servname, bool& server_closed):
        skt(servname.c_str()), server_closed(server_closed) {}

// Pre: -
// Post: -
void Aceptador::finalizar_conexion() {
    skt.shutdown(2);
    skt.close();
}

// Pre: -
// Post: -
void Aceptador::definir_conexion() {

    Socket peer = skt.accept();
    if (server_closed)
        return;

    servidores.emplace_back(server_closed);         // Creo un server y lo coloco en la lista.
    servidores.back().add_player(std::move(peer));  // Añado un jugador a ese server recien creado.

    /*
    Me gustaria poner aca diferentes servidores y que de alguna forma el jugadores elija alguno.
    De momento tenemos un solo servidor que esta creado del principio.
    */
}

// Pre: -
// Post: -
void Aceptador::run() {

    try {

        while (not server_closed) {

            definir_conexion();
        }


    } catch (const std::exception& e) {
        if (not server_closed)
            std::cerr << "Se capturó una excepción: " << e.what() << "\n";

    } catch (...) {
        std::cerr << "Se capturó una excepción desconocida.\n";
    }
}
