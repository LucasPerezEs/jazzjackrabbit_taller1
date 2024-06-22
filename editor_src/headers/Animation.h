/*
 * Created by Federico Manuel Gomez Peter
 * Date: 17/05/18.
 */

#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include <SDL2/SDL.h>

#include "SdlException.h"
#include "SdlTexture.h"

//#define FRAME_RATE 1000000.0f / 20.0f


class Animation {
public:
    Animation(const SdlTexture* texture, int numFrames, int animation_speed);
    ~Animation();
    int update(int current_frame, int& counter);
    void render(const Area& dst, const SDL_RendererFlip& flipType, int current_frame);

private:
    int advanceFrame(int current_frame);
    /** SDL texture of the raw image. */
    const SdlTexture* texture;
    /** Total number of frames in the sprite. */
    int numFrames;
    /** Size of the sprite width. */
    int size_width;
    /** Size of the sprite height. */
    int size_height;
    /** Time elapsed since last update. */
    float elapsed;
    /** Velocidad de animacion (1 - Rapido, 2 - Intermedio, 3 - Lento). */
    int animation_speed;
    /** Contador para manejar la velocidad de animacion. */
    int counter;
};

#endif  //__ANIMATION_H__
