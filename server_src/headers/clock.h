#ifndef CLOCK_H
#define CLOCK_H

#include <chrono>
#include <iostream>
#include <map>
#include <string>
#include "../../common_src/headers/Container.h"
#include "../../common_src/headers/queue.h"

#include "contenedor.h"

class Clock {
private:
    std::chrono::system_clock::time_point clock;
    int seconds;
    bool game_started;
    bool game_ended;

public:
    explicit Clock(std::map<std::string, float>& config);

    void start();

    void update(Queue<Container>& q);

    bool times_up();
};

#endif
