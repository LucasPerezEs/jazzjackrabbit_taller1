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
    Area dst(pos_x, pos_y, pos_x + texture->getWidth(), pos_y + texture->getHeight());
    texture->render(dst);
}

TTF_Font* Fuente::get_font() const { return fuente; }
