/*
 * Created by Federico Manuel Gomez Peter
 * Date: 17/05/18.
 */
#include "../headers/Animation.h"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../headers/SdlTexture.h"

Animation::Animation(const SdlTexture* texture, int numFrames, int animation_speed):
        texture(texture),
        numFrames(numFrames),
        size_width(this->texture->getWidth() / this->numFrames),
        size_height(this->texture->getHeight()),
        elapsed(0.0f),
        animation_speed(animation_speed),
        counter(1) {
    assert(this->numFrames > 0);
    assert(this->size_width > 0);
    assert(this->size_height > 0);
}

Animation::~Animation() {}

int Animation::update(int current_frame, int& counter) {
    if (counter == animation_speed) {
        counter = 1;
        return this->advanceFrame(current_frame);
    } else {
        counter++;
        return current_frame;
    }
}

/**
 * @brief Renders the animation in the given coordinates.
 *
 * @param renderer Renderer.
 * @param x X coordinate.
 * @param y Y corrdinate.
 */
void Animation::render(const Area& dst, const SDL_RendererFlip& flipType, int current_frame) {
    Area src((this->size_width) * current_frame, 0, this->size_width, this->size_height);
    this->texture->render(src, dst, flipType);
}

int Animation::advanceFrame(int current_frame) { return (current_frame + 1) % this->numFrames; }
