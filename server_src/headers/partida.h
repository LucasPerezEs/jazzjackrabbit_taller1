
#ifndef PARTIDA_H
#define PARTIDA_H

#include <chrono>
#include <functional>
#include <string>
#include <thread>
#include <variant>
#include <vector>

#include "../../common_src/headers/queue.h"
#include "../../common_src/headers/thread.h"


#include "enemigo.h"
#include "lista_objetos.h"
#include "mapa.h"
#include "objeto.h"
#include "personaje.h"

class Partida: public Thread {
private:
    bool& server_closed;

public:
    explicit Partida(bool& server_closed);

    virtual void run() override;

    Partida(const Partida&) = delete;
    Partida& operator=(const Partida&) = delete;

    Partida(Partida&&);
    Partida& operator=(Partida&&);
};

#endif
