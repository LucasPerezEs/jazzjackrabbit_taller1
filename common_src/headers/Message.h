#ifndef MESSAGE_H
#define MESSAGE_H
#include <cstdint>
#include <iostream>
#include <string>

#include "commands.h"

class Message {
public:
    enum class Type { COMMAND = 0x00, SETUP = 0x01 };

    // cppcheck-suppress uninitMemberVar
    explicit Message(Command::ActionType commandType):
            command({commandType}), type_(Type::COMMAND) {}

    // cppcheck-suppress uninitMemberVar
    explicit Message(Setup::ActionType setupType): setup({setupType, {}, {}, {}}), type_(Type::SETUP) {}

    // cppcheck-suppress uninitMemberVar
    Message(Setup::ActionType setupType, const std::string& gameId, uint32_t maxPlayers):
            setup({setupType, {}, gameId, maxPlayers, {}}), type_(Type::SETUP) {}

    // cppcheck-suppress uninitMemberVar
    Message(Setup::ActionType setupType, uint32_t character, const std::string& gameId):
            setup({setupType, {}, gameId, {}, character}), type_(Type::SETUP) {}

    Type type() const { return type_; }
    uint32_t id() const { return clientId; }
    void setId(uint32_t id) {
        clientId = id;
        command.clientId = id;
        setup.clientId = id;
    }

    Command command;
    Setup setup;

private:
    uint32_t clientId;
    Type type_;
};

#endif
