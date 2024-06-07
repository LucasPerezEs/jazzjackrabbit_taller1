#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <map>
#include <sstream>
#include <string>
#include <utility>

#include "../../common_src/headers/commands.h"
#include "../../common_src/headers/entity_commands.h"
#include "../../common_src/headers/protocol.h"
#include "../../common_src/headers/socket.h"
#include "../../server_src/headers/contenedor.h"

class ClientProtocol: public Protocol {
private:
public:
    ClientProtocol(const std::string& hostname, const std::string& servicename);

    void send_command(Command& cmd);
    std::pair<State::StateType, SpecialAction::SpecialActionType> receive_update();
    void send_join_game();
    void send_create_game();
    void send_get_game_list();
    Contenedor receive_info();

    Contenedor receiveDatosObjeto();

    ClientProtocol(const ClientProtocol&) = delete;
    ClientProtocol& operator=(const ClientProtocol&) = delete;

    ClientProtocol(ClientProtocol&&) = default;
    ClientProtocol& operator=(ClientProtocol&&) = default;

    void stop() override;

    virtual ~ClientProtocol() = default;
};

#endif
