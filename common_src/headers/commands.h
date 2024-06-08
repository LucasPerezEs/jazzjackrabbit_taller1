#ifndef COMMON_COMMANDS_H
#define COMMON_COMMANDS_H
#include <map>
#include <cstdint>

// En este archivo se pueden crear nuevos comandos.

#define GAME_TIME 90  // En segundos

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
        JOIN_GAME = 0x31,
        CREATE_GAME = 0x32,
        GET_GAME_LIST = 0x33,
    };
    ActionType action;
    // cppcheck-suppress unusedStructMember
    uint32_t clientId;
};


struct State {
    enum StateType { INTOXICATED = 0x11, DEATH = 0x12, NONE = 0x00 };
    StateType state;
};

struct SpecialAction {
    enum SpecialActionType { PUNCH = 0x21, SHORTKICK = 0x22, SIDEKICK = 0x23, NONE = 0x00 };
    SpecialActionType specialAction;
};


#endif  // COMMANDS_H
