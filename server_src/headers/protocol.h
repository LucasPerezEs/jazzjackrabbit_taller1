#ifndef SERVER_PROTOCOL_H
#define SERVER_PROTOCOL_H

#include <string>
#include <utility>
#include <vector>

#include "../../common_src/headers/commands.h"
#include "../../common_src/headers/entity_commands.h"
#include "../../common_src/headers/protocol.h"
#include "../../common_src/headers/socket.h"

#include "contenedor.h"

class ServerProtocol: private Protocol {
private:
public:
    explicit ServerProtocol(Socket peer);

    Command::ActionType receive_command();
    std::pair<Command::ActionType, uint32_t> receive_command_with_id() ;
    void send_state(State::StateType state);

    void send_id(Contenedor c);

    void send_datos_objeto(Contenedor c);

    void send_info(Contenedor c);

    ServerProtocol(const ServerProtocol&) = delete;
    ServerProtocol& operator=(const ServerProtocol&) = delete;

    void stop() override;
    void close() override;

    virtual ~ServerProtocol() = default;
};


#endif  // SERVER_PROTOCOL_H
