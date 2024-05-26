#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <SDL.h>

#include "../../common_src/headers/commands.h"
#include "../../common_src/headers/thread.h"

#include "player.h"
#include "protocol.h"

#define FRAME_RATE 1000000.0f / 40.0f

class EventHandler: public Thread {

private:
    ClientProtocol& protocol;
    Player& player;

    bool was_closed;

    void handle_keydown(const SDL_Event& event, Command& cmd );

    void handle_keyup(const SDL_Event& event);

public:
    explicit EventHandler(ClientProtocol& protocol,Player& player);

    virtual void run() override;

    bool is_running();

    void close();

    EventHandler(const EventHandler&) = delete;
    EventHandler& operator=(const EventHandler&) = delete;

    EventHandler(EventHandler&&) = default;
    EventHandler& operator=(EventHandler&&) = default;
};

#endif
