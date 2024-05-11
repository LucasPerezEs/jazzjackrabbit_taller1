#ifndef SERVER_PROTOCOL_H
#define SERVER_PROTOCOL_H

#include <string>
#include <utility>
#include <vector>

#include "../common_src/socket.h"
#include "../common_src/commands.h"
#include "../common_src/protocol.h"


class ServerProtocol: private Protocol {
private:
public:
    explicit ServerProtocol(Socket peer);

    Command::ActionType receive_command();

    void send_state(State::StateType state);


    ServerProtocol(const ServerProtocol&) = delete;
    ServerProtocol& operator=(const ServerProtocol&) = delete;

    void stop() override;
    void close() override;

    virtual ~ServerProtocol() = default;
};


#endif  // SERVER_PROTOCOL_H
