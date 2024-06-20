#include "../headers/clock.h"

Clock::Clock(std::map<std::string, float>& config):
        seconds(config["game_time"]), game_started(false), game_ended(false) {}

void Clock::start() {
    this->clock = std::chrono::system_clock::now();
    this->game_started = true;
    this->game_ended = false;
}

void Clock::update(Queue<Container>& q) {
    if (!game_started && !game_ended) {
        return;
    }

    if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() -
                                                              clock)
                .count() >= 1000) {
        this->seconds -= 1;
        this->clock = std::chrono::system_clock::now();

        // No esta muy bien conceptualmente mandar los segundos en el campo id
        Container c(4, seconds, 0, 0, 0, 0, 0, AnimationType::NONE_ANIMATION,
                    EntityType::NONE_ENTITY, 0, 0, 0);
        q.try_push(c);
    }

    if (seconds <= 0) {
        game_ended = true;
    }
}

bool Clock::times_up() { return game_ended; }
