#ifndef CLOCK_H
#define CLOCK_H

#include <chrono>
#include <iostream>

#include "../../common_src/headers/commands.h"
#include "../../common_src/headers/queue.h"

#include "contenedor.h"

class Clock {
private:
    std::chrono::system_clock::time_point clock;
    int seconds;
    bool game_started;
    bool game_ended;

public:
    Clock();

    void start();

    void update(Queue<Contenedor>& q);

    bool times_up();
};

#endif
