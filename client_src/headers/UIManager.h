#ifndef UIMANAGER_H
#define UIMANAGER_H

#include <map>

#include "../../common_src/headers/commands.h"

#include "Fuente.h"
#include "SdlWindow.h"
#include "player.h"

class UIManager {

private:
    std::map<int, Player*>& personajes;
    SdlWindow& window;
    Fuente fuente;
    std::map<int, SdlTexture*> texturas_ui;
    int clock;


    bool player_alive(int id_cliente);

public:
    UIManager(std::map<int, Player*>& personajes, SdlWindow& window);

    void update_clock(int seconds);

    void render_UI(int id_cliente);

    void renderLoadingText();
};

#endif  // UIMANAGER_H
