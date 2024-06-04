#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "../../common_src/headers/commands.h"

#include "clientReceiver.h"
#include "entity.h"
#include "event_handler.h"
#include "model_updater.h"
#include "protocol.h"
//#include "SdlWindow.h"


class Client {
public:

    Client(const std::string& hostname, const std::string& servername, Player& player,
           Queue<Contenedor>& queue, SdlWindow& window, std::map<int, Entity*>& entidades);

    void go_online();
    bool is_online();

    void set_id(int i);

    int get_id();

    void close();

private:
    ClientProtocol client_protocol;
    ClientReceiver client_receiver;
    EventHandler event_handler;  // eventos teclado (sender)
    ModelUpdater updater;        // actualizar modelos (receiver)
    Player& player;
    bool online;
    int id;

    // SdlWindow& window;
};

#endif
