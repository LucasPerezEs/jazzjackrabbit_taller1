//
//#ifndef GAME_H
//#define GAME_H
//
//#include <string>
//
//#include "aceptador.h"
//#include "partida.h"
//
//class Game {
//private:
//    const std::string& servname;
//
//public:
//    explicit Game(const std::string& servname);
//
//    void init_game();
//
//    Game(const Game&) = delete;
//    Game& operator=(const Game&) = delete;
//};
//
//#endif

#ifndef SERVER_GAME_H
#define SERVER_GAME_H

#include <iostream>
#include <memory>
#include <string>

#include "../../common_src/headers/commands.h"
#include "../../common_src/headers/queue.h"
#include "../../common_src/headers/thread.h"

class Game: public Thread {
public:
    explicit Game(Queue<Command::ActionType>& actionQueue, Queue<State::StateType>& eventQueue);

    void run() override;
    void stop() override;


    bool is_running() { return _is_alive; }

private:
    Queue<Command::ActionType>& actionQueue;

    Queue<State::StateType>& stateQueue;

};

#endif  // SERVER_GAME_H
