#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <SDL.h>

#include "../../common_src/headers/commands.h"
#include "../../common_src/headers/thread.h"

#include "camara.h"
#include "protocol.h"
#include "SoundManager.h"
#include "UIManager.h"

//#define FRAME_RATE 1000000.0f / 20.0f

class EventHandler: public Thread {

private:
    ClientProtocol& protocol;

    bool was_closed;

    bool& in_menu;

    bool& gameEnded;

    Camara* camara;

    SoundManager& sound_manager;

    UIManager& uimanager;

    void handle_keydown(const SDL_Event& event, Command& cmd);

    void handle_keyup(const SDL_Event& event, Command& cmd);

public:
    explicit EventHandler(ClientProtocol& protocol, bool& menu, bool& gameEnded, SoundManager& sound_manager, UIManager& uimanager);

    virtual void run() override;

    bool is_running();

    void close();

    void set_camara(Camara* c);

    EventHandler(const EventHandler&) = delete;
    EventHandler& operator=(const EventHandler&) = delete;

    EventHandler(EventHandler&&) = default;
    EventHandler& operator=(EventHandler&&) = default;
};

#endif
