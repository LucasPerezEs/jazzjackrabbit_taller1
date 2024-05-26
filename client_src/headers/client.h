#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <map>
#include <string>

#include "client_protocol.h"
#include "common_commands.h"

#define COMMAND_PARAMETER_START_INDEX 5

class Client {
public:
    Client(const std::string& hostname, const std::string& servername);
    void run(std::istream& in);

private:
    ClientProtocol client_protocol;
    static const std::map<std::string, Command::ActionType> actions_map;

    void receive_and_print_messages(int n);
    void sendAttack();
    void printEvent(EnemyEvent event);
    void printMessage(const std::string& msg);
};

#endif
