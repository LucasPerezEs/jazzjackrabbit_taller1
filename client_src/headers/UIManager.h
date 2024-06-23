#ifndef UIMANAGER_H
#define UIMANAGER_H

#include <map>
#include <utility>
#include <vector>

#include "../../common_src/headers/commands.h"
#include "../../common_src/headers/entity_commands.h"

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
    TTF_Font* chica;

    bool player_alive(int id_cliente);

    void render_top3();

    std::vector<std::pair<int, Player*>> top3Values(const std::map<int, Player*>& inputMap);

public:
    SDL_Rect mainMenu;
    SDL_Rect muteMusic;
    UIManager(std::map<int, Player*>& personajes, SdlWindow& window);

    void update_clock(int seconds);

    void render_UI(int id_cliente);

    void render_pause_menu();

    void renderLoadingText();

    void renderEndGame(int id_cliente);

    void renderPauseMenu();
};

#endif  // UIMANAGER_H
