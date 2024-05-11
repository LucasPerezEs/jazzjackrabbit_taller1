#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <map>
#include <sstream>
#include <string>
#include <utility>

#include "../common_src/socket.h"
#include "../common_src/commands.h"
#include "../common_src/protocol.h"

class ClientProtocol: private Protocol {
private:
public:
    ClientProtocol(const std::string& hostname, const std::string& servicename);

    void send_command(Command& cmd);

    ClientProtocol(const ClientProtocol&) = delete;
    ClientProtocol& operator=(const ClientProtocol&) = delete;

    ClientProtocol(ClientProtocol&&) = default;
    ClientProtocol& operator=(ClientProtocol&&) = default;

    void stop() override;

    virtual ~ClientProtocol() = default;
};

#endif
