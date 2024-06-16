#ifndef SERVER_PROTOCOL_H
#define SERVER_PROTOCOL_H

#include <string>
#include <utility>
#include <vector>

#include "../../common_src/headers/Message.h"
#include "../../common_src/headers/Container.h"
#include "../../common_src/headers/commands.h"
#include "../../common_src/headers/entity_commands.h"
#include "../../common_src/headers/protocol.h"
#include "../../common_src/headers/socket.h"

#include "contenedor.h"

class ServerProtocol: private Protocol {
private:
    Command::ActionType receive_command();
    Message receive_setup_message();
    Message receive_command_message();
    Message receive_create_game();
    Message receive_join_game();
    Message receive_get_game_list();

    void send_setup_container(const SetupContainer& setupContainer);
    void send_game_container(const GameContainer& gameContainer);


public:
    explicit ServerProtocol(Socket peer);

    Message receive_message();
    void send_container(const Container& container);


            void send_id(Contenedor c);
    std::string receive_game_id();
    uint32_t receive_max_players();
    void send_datos_objeto(Contenedor c);
    void send_games_ids(const std::vector<std::string>& gameIDs);

    void send_info(Contenedor c);

    ServerProtocol(const ServerProtocol&) = delete;
    ServerProtocol& operator=(const ServerProtocol&) = delete;

    void stop() override;
    void close() override;

    virtual ~ServerProtocol() = default;
};


#endif  // SERVER_PROTOCOL_H
