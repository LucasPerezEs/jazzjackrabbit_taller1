
#ifndef ACEPTADOR_H
#define ACEPTADOR_H

#include <iostream>
#include <list>
#include <string>
#include <utility>
#include "servidor.h"
#include "../common_src/socket.h"
#include "../common_src/thread.h"

class Aceptador: public Thread {
private:
    Socket skt;
    bool& server_closed;
    std::list<Servidor> servidores;

    void definir_conexion();

public:
    Aceptador(const std::string& servname, bool& server_closed);

    void finalizar_conexion();

    virtual void run() override;
};

#endif
