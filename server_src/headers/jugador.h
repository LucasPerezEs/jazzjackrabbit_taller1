
#ifndef JUGADOR_H
#define JUGADOR_H

#include <iostream>
#include <list>
#include <string>
#include <utility>
#include <variant>

#include "../../common_src/headers/socket.h"

#include "protocol.h"

class Jugador {
private:
    ServerProtocol protocolo;
    unsigned int id_jugador;
    bool jugador_online;
    bool& server_closed;

public:
    Jugador(Socket&& socket, unsigned int& id_jugador, bool& server_closed);

    bool desconectar();

    void run();

    Jugador(const Jugador&) = delete;
    Jugador& operator=(const Jugador&) = delete;

    Jugador(Jugador&&);
    Jugador& operator=(Jugador&&);
};

#endif
