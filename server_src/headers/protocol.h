#ifndef SERVER_PROTOCOL_H
#define SERVER_PROTOCOL_H

#include <string>
#include <utility>
#include <vector>

#include "../../common_src/headers/Container.h"
#include "../../common_src/headers/Message.h"
#include "../../common_src/headers/commands.h"
#include "../../common_src/headers/entity_commands.h"
#include "../../common_src/headers/protocol.h"
#include "../../common_src/headers/socket.h"


class ServerProtocol: public Protocol {
private:
    Message receive_setup_message();
    Message receive_command_message();
    Message receive_create_game();
    Message receive_join_game();
    Message receive_get_game_list();
    Message receive_create_map();
    Message receive_set_name();
    Message receive_get_map_list();

    void send_setup_container(const SetupContainer& setupContainer);
    void send_game_container(const GameContainer& gameContainer);
    void send_sound_container(const SoundContainer& soundContainer);


public:
    explicit ServerProtocol(Socket peer);

    Message receive_message();
    void send_container(const Container& container);

    ServerProtocol(const ServerProtocol&) = delete;
    ServerProtocol& operator=(const ServerProtocol&) = delete;

    void stop() override;
    void close() override;

    virtual ~ServerProtocol() = default;
};


#endif  // SERVER_PROTOCOL_H
