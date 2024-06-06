#include "../headers/SdlTexture.h"

#include <string>

#include "../headers/Fuente.h"
#include "../headers/SdlException.h"
#include "../headers/SdlWindow.h"

SdlTexture::SdlTexture(const std::string& filename, const SdlWindow& window):
        renderer(window.getRenderer()) {
    /**
     * Cargo la imagen en una superficie temporal
     */
    SDL_Surface* tmp = IMG_Load(filename.c_str());
    if (!tmp) {
        throw SdlException("Error loading texture");
    }

    /* creates a texture from the surface */
    this->texture = SDL_CreateTextureFromSurface(this->renderer, tmp);
    if (!texture) {
        SDL_FreeSurface(tmp);
        throw SdlException("Error creating texture");
    }

    this->height = tmp->h;
    this->width = tmp->w;

    /* releases the temporary surface */
    SDL_FreeSurface(tmp);
}

SdlTexture::SdlTexture(const std::string& filename, const SdlWindow& window, Color key):
        renderer(window.getRenderer()) {
    /**
     * Cargo la imagen en una superficie temporal
     */
    SDL_Surface* tmp = IMG_Load(filename.c_str());
    if (!tmp) {
        throw SdlException("Error loading texture");
    }

    SDL_SetColorKey(tmp, SDL_TRUE, SDL_MapRGB(tmp->format, key.r, key.g, key.b));

    /* creates a texture from the surface */
    this->texture = SDL_CreateTextureFromSurface(this->renderer, tmp);
    if (!texture) {
        SDL_FreeSurface(tmp);
        throw SdlException("Error creating texture");
    }

    this->height = tmp->h;
    this->width = tmp->w;

    /* releases the temporary surface */
    SDL_FreeSurface(tmp);
}

SdlTexture::SdlTexture(TTF_Font* fuente, const std::string& texto, const SdlWindow& window,
                       SDL_Color key):
        renderer(window.getRenderer()) {


    SDL_Surface* superficie_texto = TTF_RenderText_Solid(fuente, texto.c_str(), key);

    if (!superficie_texto) {
        throw SdlException(TTF_GetError());
    }

    this->texture = SDL_CreateTextureFromSurface(this->renderer, superficie_texto);
    if (!texture) {
        SDL_FreeSurface(superficie_texto);
        throw SdlException("Error creating texture");
    }

    this->height = superficie_texto->h;
    this->width = superficie_texto->w;

    /* releases the temporary surface */
    SDL_FreeSurface(superficie_texto);
}

SdlTexture::SdlTexture(const std::string& filename, const SdlWindow& window, Color key,
                       SDL_BlendMode blending, uint8_t alpha):
        SdlTexture(filename, window, key) {

    SDL_SetTextureBlendMode(this->texture, blending);
    SDL_SetTextureAlphaMod(this->texture, alpha);
}

SdlTexture::~SdlTexture() { SDL_DestroyTexture(this->texture); }

int SdlTexture::render(const Area& src, const Area& dest, const SDL_RendererFlip& flipType) const {
    return render(src, dest, 0, flipType);
}

int SdlTexture::render(const Area& dest) const {
    SDL_Rect sdlDest = {dest.getX(), dest.getY(), dest.getWidth(), dest.getHeight()};

    return SDL_RenderCopy(this->renderer, this->texture, nullptr, &sdlDest);
}

int SdlTexture::render(const Area& src, const Area& dest, float angle,
                       const SDL_RendererFlip& flipType) const {
    SDL_Rect sdlSrc = {src.getX(), src.getY(), src.getWidth(), src.getHeight()};
    SDL_Rect sdlDest = {dest.getX(), dest.getY(), dest.getWidth(), dest.getHeight()};

    return SDL_RenderCopyEx(this->renderer, this->texture, &sdlSrc, &sdlDest, angle, nullptr,
                            flipType);
}


int SdlTexture::getWidth() const { return this->width; }

int SdlTexture::getHeight() const { return this->height; }
