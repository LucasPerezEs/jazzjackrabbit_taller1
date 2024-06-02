
#ifndef ACEPTADOR_H
#define ACEPTADOR_H

#include <iostream>
#include <list>
#include <string>
#include <utility>
#include "game.h"

#include "../../common_src/headers/socket.h"
#include "../../common_src/headers/thread.h"

#include "servidor.h"

class Aceptador: public Thread {
private:
    Socket skt;
    bool& server_closed;
    std::list<Servidor> servidores;

    void definir_conexion();

public:
    Aceptador(const std::string& servname, bool& server_closed, Game& game);

    void finalizar_conexion();

    virtual void run() override;
};

#endif
