/*
 * Created by Federico Manuel Gomez Peter
 * Date: 17/05/18.
 */

#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include <SDL2/SDL.h>

#include "SdlException.h"

#define FRAME_RATE 1000000.0f / 60.0f

class SdlTexture;
class Area;

class Animation {
public:
    Animation(const SdlTexture* texture, int numFrames);
    ~Animation();
    void update(float dt);
    void render(const Area& dst, const SDL_RendererFlip& flipType);


private:
    void advanceFrame();
    /** SDL texture of the raw image. */
    const SdlTexture* texture;
    /** Current animation frame. */
    int currentFrame;
    /** Total number of frames in the sprite. */
    int numFrames;
    /** Size of the sprite width. */
    int size_width;
    /** Size of the sprite height. */
    int size_height;
    /** Time elapsed since last update. */
    float elapsed;
};

#endif  //__ANIMATION_H__
