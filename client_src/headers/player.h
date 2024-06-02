#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Animation.h"
#include <utility>

class Player {
public:
    explicit Player(SdlTexture& texture);
    ~Player();
    void update(float dt);
    void render();
    void moveRigth();
    void moveLeft();
    void stopMoving();

private:
    Animation an;
    bool facingLeft;
    bool moving;
    int x;
    int y;
};

#endif  // __PLAYER_H__
