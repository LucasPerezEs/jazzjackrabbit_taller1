#include "../headers/Fuente.h"

#include <iostream>

Fuente::Fuente(const std::string& archivo_fuente, int tamano) {
    fuente = TTF_OpenFont(archivo_fuente.c_str(), tamano);
    if (fuente == nullptr) {
        std::cerr << "Error al cargar la fuente: " << TTF_GetError() << std::endl;
    }
}

Fuente::~Fuente() {
    if (fuente != nullptr) {
        TTF_CloseFont(fuente);
    }
}

void Fuente::render(float pos_x, float pos_y, const std::string& texto, const SdlWindow& window,
                    SDL_Color color) {
    SdlTexture* texture = new SdlTexture(this->fuente, texto, window, color);
    int fixed_height = 50;
    int max_width = 300;
    int min_width = 25;

    float aspect_ratio = static_cast<float>(texture->getWidth() / texture->getHeight());
    int scaled_width = static_cast<int>(fixed_height * aspect_ratio);

    if (scaled_width > max_width) {
        scaled_width = max_width;
    }

    if (scaled_width < min_width) {
        scaled_width = min_width;
    }

    Area dst(pos_x, pos_y, scaled_width, fixed_height);
    texture->render(dst);
}

TTF_Font* Fuente::get_font() const { return fuente; }
