
#ifndef GAME_H
#define GAME_H

#include <string>
#include "aceptador.h"
#include "partida.h"

class Game {
private:
    const std::string& servname;

public:
    explicit Game(const std::string& servname);

    void init_game();

    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;
};

#endif
