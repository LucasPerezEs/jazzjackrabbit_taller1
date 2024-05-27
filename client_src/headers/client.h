#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <map>
#include <string>

#include "../../common_src/headers/commands.h"

#include "SdlWindow.h"
#include "event_handler.h"
#include "model_updater.h"
#include "protocol.h"


class Client {
public:
    Client(const std::string& hostname, const std::string& servername, Player& player,
           SdlWindow& window);

    void go_online();
    bool is_online();


    void close();

private:
    ClientProtocol client_protocol;
    EventHandler event_handler;  // eventos teclado (sender)
    ModelUpdater updater;        // actualizar modelos (receiver)
    bool online;

    // SdlWindow& window;
};

#endif
