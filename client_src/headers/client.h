#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <map>
#include <string>

#include "protocol.h"
#include "../../common_src/headers/commands.h"
#include "event_handler.h"
#include "model_updater.h"
//#include "SdlWindow.h"


class Client {
public:
    Client(const std::string& hostname, const std::string& servername, Player& player);

    void go_online();
    bool is_online();


    void close();

private:
    ClientProtocol client_protocol;
    EventHandler event_handler; //eventos teclado (sender)
    ModelUpdater updater;//actualizar modelos (receiver)
    Player& player;
    bool online;

    //SdlWindow& window;


};

#endif
