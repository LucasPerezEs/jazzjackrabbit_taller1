#ifndef UIMANAGER_H
#define UIMANAGER_H

#include <map>

#include "Fuente.h"
#include "SdlWindow.h"
#include "player.h"

class UIManager {

private:
    std::map<int, Player*>& personajes;
    SdlWindow& window;
    Fuente fuente;
    std::map<int, SdlTexture*> texturas_ui;


    bool player_alive(int id_cliente);

public:
    UIManager(std::map<int, Player*>& personajes, SdlWindow& window);

    void render_UI(int id_cliente);
};

#endif  // UIMANAGER_H
