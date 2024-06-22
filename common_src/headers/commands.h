#ifndef COMMON_COMMANDS_H
#define COMMON_COMMANDS_H

#include <cstdint>
#include <map>
#include <string>
#include <vector>
// En este archivo se pueden crear nuevos comandos.

struct Command {
    enum ActionType {
        NONE = 0x00,
        UP = 0x01,
        DOWN = 0x02,
        LEFT = 0x03,
        RIGHT = 0x04,
        RUN = 0x05,
        RUNFAST = 0x06,
        JUMP = 0x07,
        FIRE = 0x08,
        STOPLEFT = 0x09,
        STOPRIGHT = 0x10,
        STOPFIRE = 0x11,
        SPECIAL = 0x12,
        QUIT = 0x13,
    };
    ActionType action;

    // cppcheck-suppress unusedStructMember
    uint32_t clientId;
};

struct Setup {
    enum ActionType {
        NONE = 0x00,
        JOIN_GAME = 0x31,
        CREATE_GAME = 0x32,
        GET_GAME_LIST = 0x33,
        CLIENT_ID = 0x34,
        CREATE_MAP = 0x35,
        SAVE_MAP = 0x36,
    };
    ActionType action;

    // cppcheck-suppress unusedStructMember
    uint32_t clientId;
    std::string gameId;
    // cppcheck-suppress unusedStructMember
    uint32_t maxPlayers;
    // cppcheck-suppress unusedStructMember
    uint32_t character;
    std::string mapName;
    std::vector<std::vector<std::string>> map;
    std::vector<uint32_t> cheats;
};

#endif  // COMMANDS_H
