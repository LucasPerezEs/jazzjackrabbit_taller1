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

struct GameData {
    // cppcheck-suppress unusedStructMember
    int id;
    // cppcheck-suppress unusedStructMember
    float x;
    // cppcheck-suppress unusedStructMember
    float y;
    // cppcheck-suppress unusedStructMember
    float width;
    // cppcheck-suppress unusedStructMember
    float height;
    // cppcheck-suppress unusedStructMember
    int direction;
    AnimationType an;
    EntityType en;
    // cppcheck-suppress unusedStructMember
    int health;
    // cppcheck-suppress unusedStructMember
    int ammo;
    // cppcheck-suppress unusedStructMember
    int score;
};

class ClientProtocol: public Protocol {
private:
    void send_setup(const Setup& setup);
    void send_command(const Command& cmd);
    void send_join_game(const std::string& gameId, const int character);
    void send_create_game(const std::string& gameId, const uint32_t& maxPlayers);
    void send_get_game_list();

    Container receive_setup_container();
    Container receive_game_container();
    Container receive_create_game();
    Container receive_join_game();
    Container receive_get_game_list();
    Container receive_client_id();

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
