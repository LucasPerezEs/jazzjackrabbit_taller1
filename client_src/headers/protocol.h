#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <map>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include "../../common_src/headers/Container.h"
#include "../../common_src/headers/Message.h"
#include "../../common_src/headers/commands.h"
#include "../../common_src/headers/entity_commands.h"
#include "../../common_src/headers/protocol.h"
#include "../../common_src/headers/socket.h"


class ClientProtocol: public Protocol {
private:
    void send_setup(const Setup& setup);
    void send_command(const Command& cmd);
    void send_join_game(const std::string& gameId, const int character);
    void send_create_game(const std::string& gameId, const uint32_t& maxPlayers, const std::string& mapName,
                          const std::vector<uint32_t>& cheats);
    void send_save_map(const std::string& mapName, const std::vector<std::vector<std::string>>& map);
    void send_create_map(const std::string& mapName);
    void send_get_game_list();
    void send_set_name(const std::string& clientName);

    Container receive_setup_container();
    Container receive_game_container();
    Container receive_sound_container();
    Container receive_create_game();
    Container receive_join_game();
    Container receive_get_game_list();
    Container receive_client_id();
    Container receive_create_map();
    Container receive_saved_map();
    Container receive_saved_name();

public:
    ClientProtocol(const std::string& hostname, const std::string& servicename);

    void send_message(const Message& message);
    Container receive_container();

    ClientProtocol(const ClientProtocol&) = delete;
    ClientProtocol& operator=(const ClientProtocol&) = delete;

    ClientProtocol(ClientProtocol&&) = default;
    ClientProtocol& operator=(ClientProtocol&&) = default;

    void stop() override;

    virtual ~ClientProtocol() = default;
};

#endif
