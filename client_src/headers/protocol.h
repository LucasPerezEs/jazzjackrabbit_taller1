#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <map>
#include <sstream>
#include <string>
#include <utility>

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
    void send_join_game(const std::string& gameId);
    void send_create_game(const std::string& gameId, const uint32_t& maxPlayers);
    void send_get_game_list();

    Container receive_setup_container();
    Container receive_game_container();

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
