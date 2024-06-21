#ifndef TEXTURE_IDS
#define TEXTURE_IDS

enum EntityType {
    JAZZ = 0x00,
    LORI = 0x01,
    SPAZ = 0x02,
    GHOST = 0x03,
    BAT = 0x04,
    BULLET = 0x05,
    AMMO = 0x06,
    CARROT = 0x07,
    GOLD_COIN = 0x08,
    NONE_ENTITY = 0x09,
    BANANA = 0x10,
    MONKEY = 0x11,
    INTOXICATED_CARROT = 0x12
};

enum AnimationType {
    IDLE = 0x10,
    WALK = 0x11,
    RUN = 0x12,
    JUMP = 0x13,
    FALL = 0x14,
    RECIEVE_DAMAGE = 0x15,
    DEAD = 0x16,
    SPECIAL_ACTION = 0x17,
    INTOXICATED_WALK = 0x18,
    PICKUP = 0x19,
    NONE_ANIMATION = 0x20,
    SHOOT = 0x21,
    SHOOT_IDLE = 0x22,
    FLY = 0x23,
    HURT = 0x24
};

enum AnimationSpeed { FAST = 1, DEFAULT = 2, SLOW = 3 };

#endif
