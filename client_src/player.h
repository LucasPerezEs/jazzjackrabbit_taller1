#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "./sdl_libs/Animation.h"
#include "./sdl_libs/Area.h"

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
