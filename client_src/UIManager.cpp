#include "headers/UIManager.h"

#include <algorithm>
#include <map>
#include <string>
#include <vector>

std::vector<std::pair<int, Player*>> orderedValues(const std::map<int, Player*>& inputMap,
                                                   bool all) {

    std::vector<std::pair<int, Player*>> mapVector(inputMap.begin(), inputMap.end());

    std::sort(mapVector.begin(), mapVector.end(),
              [](const std::pair<int, Player*>& a, const std::pair<int, Player*>& b) {
                  return a.second->get_score() > b.second->get_score();
              });

    std::vector<std::pair<int, Player*>> orderedValues;

    if (all) {
        for (const auto& elem: mapVector) {
            // cppcheck-suppress useStlAlgorithm
            orderedValues.push_back(elem);
        }
    } else {
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

    mainMenuBorder.x = 255;
    mainMenuBorder.y = 480;
    mainMenuBorder.w = 290;
    mainMenuBorder.h = 50;

    muteMusic.x = 800 / 2 - 140;
    muteMusic.w = 280;
    muteMusic.y = 600 / 2 - 25;
    muteMusic.h = 50;


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
    this->texturas_ui[5] = new SdlTexture("../client_src/assets/textures/ui_icebullet.png", window,
                                          Color{0x2C, 0x66, 0x96});

    this->texturas_ui[6] = new SdlTexture("../client_src/assets/loading/loading.png", window);
}

bool UIManager::player_alive(int id_cliente) { return personajes.count(id_cliente) > 0; }

void UIManager::update_clock(int seconds) { this->clock = seconds; }

void UIManager::render_top3() {
    SDL_Color amarillo = {237, 206, 69, 255};
    std::vector<std::pair<int, Player*>> score = orderedValues(personajes, false);
    for (long unsigned int i = 0; i < score.size(); i++) {
        std::string string =
                score[i].second->get_name() + "  " + std::to_string(score[i].second->get_score());
        SdlTexture* texture = new SdlTexture(chica, string, window, amarillo);

        Area dst(640, 28 + 25 * (i + 1), string.size() * 9, 30);
        texture->render(dst);
        delete texture;
    }
}

void UIManager::render_UI(int id_cliente) {
    SDL_Color amarillo = {237, 206, 69, 255};
    SDL_Color rojo = {252, 3, 3, 255};

    if (!player_alive(id_cliente)) {
        this->fuente.render(10, 10, "DEAD", window, rojo);
        this->fuente.render(400 - 20, 15, std::to_string(this->clock), window, amarillo);
        return;
    }

    //   ScoreBoard
    this->fuente.render(590, 5, "ScoreBoard", window, amarillo);
    render_top3();

    Player* personaje = personajes[id_cliente];

    int fixed_size = 50;

    Area dst_v(10, 10, fixed_size, fixed_size);
    texturas_ui[0]->render(dst_v);

    Area dst_a(10, 10 + fixed_size, fixed_size, fixed_size);
    switch (personaje->get_municion().ammo_type) {
        case BULLET:
            texturas_ui[3]->render(dst_a);
            break;
        case ROCKET:
            texturas_ui[4]->render(dst_a);
            break;
        case ICE_BULLET:
            texturas_ui[5]->render(dst_a);
            break;
        default:
            break;
    }


    Area dst_s(10, 10 + 2 * fixed_size, fixed_size, fixed_size);
    texturas_ui[2]->render(dst_s);


    this->fuente.render(10 + fixed_size, 15, std::to_string(personaje->get_vida()), window,
                        amarillo);
    this->fuente.render(10 + fixed_size, 15 + fixed_size,
                        std::to_string(personaje->get_municion().ammo), window, amarillo);
    this->fuente.render(10 + fixed_size, 15 + 2 * fixed_size,
                        std::to_string(personaje->get_score()), window, amarillo);

    if (this->clock != -1) {
        this->fuente.render(400 - 20, 15, std::to_string(this->clock), window, amarillo);
    }
}

void UIManager::renderPauseMenu() {
    SDL_Color amarillo = {237, 206, 69, 255};

    SDL_Rect button;
    button.x = 800 / 2 - 140;
    button.w = 280;
    button.y = 600 / 2 - 25;
    button.h = 50;
    SDL_SetRenderDrawColor(window.getRenderer(), 0, 0, 0, 255);
    SDL_RenderFillRect(window.getRenderer(), &button);

    this->fuente.render(800 / 2 - 100, 600 / 2 - 25, "Pause   Music", window, amarillo);
}

void UIManager::renderLoadingText() {
    this->fuente.render(800 / 2 - 100, 600 / 2 + 120, "Waiting       players", window, {0, 0, 0});
}

void UIManager::renderEndGame(int id_cliente) {
    // window.fill(70, 130, 180, 255);
    Area dst(0, 0, 800, 600);
    texturas_ui[6]->render(dst);

    SDL_Rect buttonBorder;
    buttonBorder.x = 190;
    buttonBorder.y = 20;
    buttonBorder.w = 420;
    buttonBorder.h = 100;
    SDL_SetRenderDrawColor(window.getRenderer(), 0, 0, 0, 255);
    SDL_RenderFillRect(window.getRenderer(), &buttonBorder);

    SDL_Rect button;
    button.x = 200;
    button.y = 30;
    button.w = 400;
    button.h = 80;
    SDL_SetRenderDrawColor(window.getRenderer(), 55, 7, 51, 255);
    SDL_RenderFillRect(window.getRenderer(), &button);


    std::vector<std::pair<int, Player*>> score = orderedValues(personajes, true);

    if (score[0].second->get_name() == personajes[id_cliente]->get_name()) {
        this->fuente.render(225, 35, 350, 80, "Winner      winner      chicken      dinner", window,
                            {237, 206, 69, 255});
    } else {
        this->fuente.render(225, 35, 350, 80, "You      Lose", window, {237, 206, 69, 255});
    }

    SDL_Rect scoreBorder;
    scoreBorder.x = 295;
    scoreBorder.y = 110;
    scoreBorder.w = 210;
    scoreBorder.h = 50;
    SDL_SetRenderDrawColor(window.getRenderer(), 0, 0, 0, 255);
    SDL_RenderFillRect(window.getRenderer(), &scoreBorder);

    SDL_Rect scoreFill;
    scoreFill.x = 305;
    scoreFill.y = 120;
    scoreFill.w = 190;
    scoreFill.h = 30;
    SDL_SetRenderDrawColor(window.getRenderer(), 55, 7, 51, 255);
    SDL_RenderFillRect(window.getRenderer(), &scoreFill);

    this->fuente.render(310, 122, 180, 26, "Scoreboard", window, {237, 206, 69, 255});

    float score_size_factor;
    if (score.size() > 3) {
        score_size_factor = 0.5;
    } else {
        score_size_factor = 1;
    }

    for (long unsigned int i = 0; i < score.size(); i++) {

        std::string string = std::to_string(i + 1) + "   " + score[i].second->get_name() +
                             "                                                  " +
                             std::to_string(score[i].second->get_score());
        this->fuente.render(200, 325 + i * 50, 400 * score_size_factor, 50 * score_size_factor,
                            string, window, {0, 0, 0, 255});
    }

    SDL_SetRenderDrawColor(window.getRenderer(), 0, 0, 0, 255);
    SDL_RenderFillRect(window.getRenderer(), &mainMenuBorder);

    /*SDL_Rect mainMenuFill;
    mainMenuFill.x = 265;
    mainMenuFill.y = 500;
    mainMenuFill.w = 270;
    mainMenuFill.h = 30;
    SDL_SetRenderDrawColor(window.getRenderer(), 55, 7, 51, 255);
    SDL_RenderFillRect(window.getRenderer(), &mainMenuFill);*/

    this->fuente.render(mainMenuBorder.x + 25, mainMenuBorder.y + 15, mainMenuBorder.w - 50,
                        mainMenuBorder.h - 30, "Main Menu", window, {237, 206, 69, 255});
}
