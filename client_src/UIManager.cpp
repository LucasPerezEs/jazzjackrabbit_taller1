#include "headers/UIManager.h"

UIManager::UIManager(std::map<int, Player*>& personajes, SdlWindow& window):
        personajes(personajes),
        window(window),
        fuente("../client_src/assets/ARCADECLASSIC.TTF", 32),
        clock(GAME_TIME) {
    this->texturas_ui[0] =
            new SdlTexture("../client_src/assets/ui_vida.png", window, Color{0x2C, 0x66, 0x96});
    this->texturas_ui[1] =
            new SdlTexture("../client_src/assets/ui_ammo.png", window, Color{0x2C, 0x66, 0x96});
    this->texturas_ui[2] =
            new SdlTexture("../client_src/assets/ui_score.png", window, Color{0x2C, 0x66, 0x96});
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

    this->fuente.render(700, 15, std::to_string(this->clock), window, amarillo);
}
