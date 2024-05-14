#ifndef CONTROLADOR_CLIENTE_H
#define CONTROLADOR_CLIENTE_H

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <SDL.h>

#include "../common_src/commands.h"

#include "player.h"
#include "protocol.h"

class ControladorCliente {

private:
    ClientProtocol protocolo;

    void handle_keydown(Player& player, const SDL_Event& event, Command& cmd);

    void handle_keyup(Player& player, const SDL_Event& event);

public:
    ControladorCliente(const std::string& hostname, const std::string& servname);

    bool handle_events(Player& player);

    ControladorCliente(const ControladorCliente&) = delete;
    ControladorCliente& operator=(const ControladorCliente&) = delete;

    ControladorCliente(ControladorCliente&&) = default;
    ControladorCliente& operator=(ControladorCliente&&) = default;
};

#endif
