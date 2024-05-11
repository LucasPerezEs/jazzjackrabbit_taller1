#ifndef COMMON_COMMANDS_H
#define COMMON_COMMANDS_H
#include <map>
// En este archivo se pueden crear nuevos comandos.

struct Command {
    enum ActionType { UP = 0x01, DOWN = 0x02, LEFT = 0x03, RIGHT = 0x04, RUN = 0x05, RUNFAST = 0x06, JUMP = 0x07 };
    ActionType action;
};

struct State {
    enum StateType { INTOXICATED = 0x11, DEATH = 0x12 };
    StateType state;
};

struct SpecialAction {
    enum SpecialActionType { PUNCH = 0x21, SHORTKICK = 0x22, SIDEKICK = 0x22  };
    SpecialActionType specialAction;
};


#endif  // COMMANDS_H
