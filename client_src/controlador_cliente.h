#ifndef CONTROLADOR_CLIENTE_H
#define CONTROLADOR_CLIENTE_H

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <SDL.h>
#include "protocol.h"

class ControladorCliente {

private:
    ClientProtocol protocolo;

public:
    ControladorCliente(const std::string& hostname, const std::string& servname);

    void jugar();

    ControladorCliente(const ControladorCliente&) = delete;
    ControladorCliente& operator=(const ControladorCliente&) = delete;

    ControladorCliente(ControladorCliente&&) = default;
    ControladorCliente& operator=(ControladorCliente&&) = default;
};

#endif
