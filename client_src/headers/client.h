#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "../../common_src/headers/commands.h"

#include "UIManager.h"
#include "clientReceiver.h"
#include "entity.h"
#include "event_handler.h"
#include "model_updater.h"
#include "player.h"
#include "protocol.h"
// #include "SdlWindow.h"


class Client {
public:
    Client(const std::string& hostname, const std::string& servername);

    bool createGame(const std::string& gameId, const std::string& mapName, const uint32_t maxPlayers,
                    const std::vector<uint32_t>& cheats);

    bool createMap(const std::string& mapName, std::vector<std::vector<std::string>>& mapReceived);

    bool saveMap(const std::string& mapName, std::vector<std::vector<std::string>>& mapSended);

    bool joinGame(const std::string& gameId, const int elegido);
    bool refreshGameList(std::vector<std::string>& gameList);

    bool setName(const std::string& clientName);

    void go_online();
    bool is_online();

    void set_id(int i);
    int get_id();

    std::vector<std::vector<std::string>> getMap();


    ClientProtocol& get_protocol();
    std::string mapName;
    std::vector<std::vector<std::string>> map;

    void close();

private:
    ClientProtocol client_protocol;
    // ClientReceiver client_receiver;
    // EventHandler event_handler;  // eventos teclado (sender)
    // ModelUpdater updater;        // actualizar modelos (receiver)
    bool online;
    int id;

    // SdlWindow& window;
};

#endif
