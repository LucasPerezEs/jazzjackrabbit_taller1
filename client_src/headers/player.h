#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <utility>

#include "Animation.h"

class Player {
public:
    explicit Player(SdlTexture& texture);
    ~Player();
    void update(float dt);
    void render();
    void moveRigth();
    void moveLeft();
    void stopMoving();
    void change_animation(SdlTexture* texture, int n_frames);

private:
    Animation an;
    bool facingLeft;
    bool moving;
    int x;
    int y;
};

#endif  // __PLAYER_H__
