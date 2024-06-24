#ifndef FUENTE_H
#define FUENTE_H

#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "SdlTexture.h"

class Fuente {

private:
    TTF_Font* fuente;

public:
    Fuente(const std::string& font_path, int font_size);

    void render(float pos_x, float pos_y, const std::string& texto, const SdlWindow& window,
                SDL_Color color);

    void render(float pos_x, float pos_y, float widht, float hight, const std::string& texto, const SdlWindow& window,
                SDL_Color color);

    TTF_Font* get_font() const;

    ~Fuente();
};

#endif  // FUENTE_H
