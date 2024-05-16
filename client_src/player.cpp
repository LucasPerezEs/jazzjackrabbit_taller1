#include "headers/player.h"

Player::Player(SdlTexture& texture):
        an(&texture, 8), facingLeft(false), moving(false), x(300), y(300) {}

Player::~Player() {}

void Player::update(float dt) {
    if (moving) {
        an.update(dt);
        if (facingLeft)
            x -= 15;
        else
            x += 15;
    }
}

void Player::render() {
    SDL_RendererFlip flip = facingLeft ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
    Area destArea(x, y, 200, 200);
    an.render(destArea, flip);
}

void Player::moveRigth() {
    moving = true;
    facingLeft = false;
}

void Player::moveLeft() {
    moving = true;
    facingLeft = true;
}

void Player::stopMoving() { moving = false; }
