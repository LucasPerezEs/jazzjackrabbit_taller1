#include "headers/UIManager.h"

#include <algorithm>
#include <map>
#include <string>
#include <vector>


UIManager::UIManager(std::map<int, Player*>& personajes, SdlWindow& window):
        personajes(personajes),
        window(window),
        fuente("../client_src/assets/ARCADECLASSIC.TTF", 32),
        clock(-1),
        chica(TTF_OpenFont("../client_src/assets/ARCADECLASSIC.TTF", 18)) {
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

std::vector<std::pair<int, Player*>> UIManager::top3Values(const std::map<int, Player*>& inputMap) {
    // Vector para almacenar los pares del mapa
    std::vector<std::pair<int, Player*>> mapVector(inputMap.begin(), inputMap.end());

    // Ordenar el vector por el segundo elemento del par (valor) en orden descendente
    std::sort(mapVector.begin(), mapVector.end(),
              [](const std::pair<int, Player*>& a, const std::pair<int, Player*>& b) {
                  return a.second->get_score() > b.second->get_score();
              });

    // Vector para almacenar el top 3
    std::vector<std::pair<int, Player*>> top3;
    int count = 0;

    // Obtener los primeros 3 elementos del vector ordenado
    for (const auto& elem: mapVector) {
        if (count < 3) {
            top3.push_back(elem);
            count++;
        } else {
            break;
        }
    }

    return top3;
}
bool UIManager::player_alive(int id_cliente) { return personajes.count(id_cliente) > 0; }

void UIManager::update_clock(int seconds) { this->clock = seconds; }

void UIManager::render_top3() {
    SDL_Color amarillo = {237, 206, 69, 255};
    std::vector<std::pair<int, Player*>> score = top3Values(personajes);
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
        render_top3();
        return;
    }

    //   ScoreBoard
    this->fuente.render(590, 5, "ScoreBoard", window, amarillo);
    /*std::string string_board = "Score Board";
    SdlTexture* texture_c = new SdlTexture(chica, string_board, window, amarillo);

    Area dst_r(620, 5, string_board.size() * 9, 30);
    texture_c->render(dst_r);
    delete texture_c;*/

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

void UIManager::renderLoadingText() {
    this->fuente.render(800 / 2 - 100, 600 / 2 + 120, "Waiting       players", window, {0, 0, 0});
}
