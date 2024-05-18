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

class EventHandler: public Thread {

private:
    ClientProtocol protocolo;

    bool was_closed;

    void handle_keydown(const SDL_Event& event, Command& cmd);

    void handle_keyup(const SDL_Event& event);

public:
    EventHandler(const std::string& hostname, const std::string& servname);

    virtual void run() override;

    bool is_running();

    EventHandler(const EventHandler&) = delete;
    EventHandler& operator=(const EventHandler&) = delete;

    EventHandler(EventHandler&&) = default;
    EventHandler& operator=(EventHandler&&) = default;
};

#endif
