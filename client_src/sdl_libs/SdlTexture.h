#ifndef __SDL_TEXTURE_H__
#define __SDL_TEXTURE_H__
#include <cstdint>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class SDL_Texture;
class SDL_Renderer;
class SdlWindow;
class Area;

struct Color {
    // cppcheck-suppress unusedStructMember
    uint8_t r, g, b;
};

class SdlTexture {
public:
    /**
     * Crea un SDL_Texture, lanza una excepción si el filename es inválido
     **/
    SdlTexture(const std::string& filename, const SdlWindow& window, Color key,
               SDL_BlendMode blending, uint8_t alpha);
    SdlTexture(const std::string& filename, const SdlWindow& window, Color key);
    SdlTexture(const std::string& filename, const SdlWindow& window);
    /**
     * Libera la memoria reservada por la textura
     **/
    ~SdlTexture();
    /**
     * Renderiza la textura cargada
     **/
    int render(const Area& src, const Area& dest,
               const SDL_RendererFlip& flipType = SDL_FLIP_NONE) const;
    int render(const Area& src, const Area& dest, float angle,
               const SDL_RendererFlip& flip = SDL_FLIP_NONE) const;
    /**
     * Getters de las dimensiones de la textura
     */
    int getWidth() const;
    int getHeight() const;

private:
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    int width{0};
    int height{0};
};

#endif
