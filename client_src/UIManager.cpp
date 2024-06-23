#include "headers/UIManager.h"

#include <algorithm>
#include <map>
#include <string>
#include <vector>

std::vector<std::pair<int, Player*>> orderedValues(const std::map<int, Player*>& inputMap, bool all) {
    
    std::vector<std::pair<int, Player*>> mapVector(inputMap.begin(), inputMap.end());

    std::sort(mapVector.begin(), mapVector.end(),
              [](const std::pair<int, Player*>& a, const std::pair<int, Player*>& b) {
                  return a.second->get_score() > b.second->get_score();
              });

    std::vector<std::pair<int, Player*>> orderedValues;

    if (all) {
        for (const auto& elem: mapVector) {
            orderedValues.push_back(elem);
        }
    }
    else {
        int count = 0;
        for (const auto& elem: mapVector) {
            if (count < 3) {
                orderedValues.push_back(elem);
                count++;
            } else {
                break;
            }
        }
    }

    return orderedValues;
}


UIManager::UIManager(std::map<int, Player*>& personajes, SdlWindow& window):
        personajes(personajes),
        window(window),
        fuente("../client_src/assets/ARCADECLASSIC.TTF", 32),
        clock(-1),
        chica(TTF_OpenFont("../client_src/assets/ARCADECLASSIC.TTF", 18)) {
    
    mainMenu.x = 800 - 200;
    mainMenu.w = 150;
    mainMenu.y = 600/2  - 25;
    mainMenu.h = 35;

    muteSound.x = 800/4 + 800/4 - 70;
    muteSound.w = 140;
    muteSound.y = 600/4 + 600/4 - 15;
    muteSound.h = 30;

    this->texturas_ui[0] = new SdlTexture("../client_src/assets/textures/ui_vida.png", window,
                                          Color{0x2C, 0x66, 0x96});
    this->texturas_ui[1] = new SdlTexture("../client_src/assets/textures/ui_ammo.png", window,
                                          Color{0x2C, 0x66, 0x96});
    this->texturas_ui[2] = new SdlTexture("../client_src/assets/textures/ui_score.png", window,
                                          Color{0x2C, 0x66, 0x96});
    this->texturas_ui[3] = new SdlTexture("../client_src/assets/textures/ui_bullet.png", window,
                                          Color{0x2C, 0x66, 0x96});
    this->texturas_ui[4] = new SdlTexture("../client_src/assets/textures/ui_rocket.png", window,
                                          Color{0x2C, 0x66, 0x96});
}

bool UIManager::player_alive(int id_cliente) { return personajes.count(id_cliente) > 0; }

void UIManager::update_clock(int seconds) { this->clock = seconds; }

void UIManager::render_UI(int id_cliente) {
    SDL_Color amarillo = {237, 206, 69, 255};
    SDL_Color rojo = {252, 3, 3, 255};

    if (!player_alive(id_cliente)) {
        this->fuente.render(10, 10, "DEAD", window, rojo);
        this->fuente.render(700, 15, std::to_string(this->clock), window, amarillo);
        return;
    }

    //   ScoreBoard
    std::string string_board = "Score Board";
    SdlTexture* texture_c = new SdlTexture(chica, string_board, window, amarillo);

    Area dst_r(620, 5, string_board.size() * 9, 30);
    texture_c->render(dst_r);
    delete texture_c;

    std::vector<std::pair<int, Player*>> score = orderedValues(personajes, false);
    for (long unsigned int i = 0; i < score.size(); i++) {
        std::string string = std::to_string(i + 1) + "   " + score[i].second->get_name() + "  " +
                             std::to_string(score[i].second->get_score());
        SdlTexture* texture = new SdlTexture(chica, string, window, amarillo);

        Area dst(600, 5 + 30 * (i + 1), string.size() * 9, 30);
        texture->render(dst);
        delete texture;
    }

    Player* personaje = personajes[id_cliente];

    int fixed_size = 50;

    Area dst_v(10, 10, fixed_size, fixed_size);
    texturas_ui[0]->render(dst_v);

    Area dst_a(10, 10 + fixed_size, fixed_size, fixed_size);
    texturas_ui[1]->render(dst_a);

    Area dst_s(10, 10 + 2 * fixed_size, fixed_size, fixed_size);
    texturas_ui[2]->render(dst_s);


    this->fuente.render(10 + fixed_size, 15, std::to_string(personaje->get_vida()), window,
                        amarillo);
    this->fuente.render(10 + fixed_size, 15 + fixed_size, std::to_string(personaje->get_municion()),
                        window, amarillo);
    this->fuente.render(10 + fixed_size, 15 + 2 * fixed_size,
                        std::to_string(personaje->get_score()), window, amarillo);

    if (this->clock != -1) {
        this->fuente.render(400 - 20, 15, std::to_string(this->clock), window, amarillo);
    }
}

void UIManager::renderLoadingText() {
    this->fuente.render(800 / 2 - 140, 600 / 2 + 120, "Waiting       players", window, {0, 0, 0});
}

void UIManager::renderEndGame(int id_cliente) {
    window.fill(70, 130, 180, 255);

    std::vector<std::pair<int, Player*>> score = orderedValues(personajes, true);  

    if (score[0].second->get_name() == personajes[id_cliente]->get_name()) {
        this->fuente.render(250, 50, 300, 50, "Winner      winner      chicken      dinner", window, {237, 206, 69, 255});
    }  
    else {
        this->fuente.render(350, 50, 100, 50, "You      Lose", window, {237, 206, 69, 255});
    }

    this->fuente.render(250, 150, 100, 50, "Scoreboard", window, {0, 0, 0, 255});

    for (long unsigned int i = 0; i < score.size(); i++) {
        std::string string = std::to_string(i + 1) + "   " + score[i].second->get_name();
        this->fuente.render(200, 200 + i*50, string.size()*10, 30, string, window, {237, 206, 69, 255});

        this->fuente.render(400, 200 + i*50, std::to_string(score[i].second->get_score()).size()*10, 30, std::to_string(score[i].second->get_score()), window, {237, 206, 69, 255});
    }

    SDL_SetRenderDrawColor(window.getRenderer(), 255, 255, 255, 255);
    SDL_RenderFillRect(window.getRenderer(), &mainMenu);
    this->fuente.render(mainMenu.x + 10, mainMenu.y+5, mainMenu.w - 10, mainMenu.h-5, "Main    Menu", window, {0, 0, 0, 255});
}

void UIManager::renderPauseMenu() {
        SDL_Rect background;
        background.x = 800/4;
        background.w = 800*2/4;
        background.y = 600/4;
        background.h = 600*2/4;
        SDL_SetRenderDrawColor(window.getRenderer(), 70, 130, 180, 255);
        SDL_RenderFillRect(window.getRenderer(), &background);

        SDL_SetRenderDrawColor(window.getRenderer(), 255, 255, 255, 255);
        SDL_RenderFillRect(window.getRenderer(), &muteSound);
}
