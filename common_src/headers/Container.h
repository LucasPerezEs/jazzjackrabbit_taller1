#ifndef CONTAINER_H_
#define CONTAINER_H_

#include <cstdint>
#include <string>
#include <vector>

#include "entity_commands.h"

class SetupContainer {
private:
    std::string _gameId;
    uint32_t _maxPlayers;
    bool _ok;

public:
    SetupContainer(uint32_t msg_code, const std::string& gameId, uint32_t maxPlayers, bool ok);

    std::string gameId() const;
    uint32_t maxPlayers() const;
    bool ok() const;
};

class GameContainer {
public:
    GameContainer(uint32_t msg_code, int id, float x, float y, float w, float h, int direction,
                  AnimationType an_type, EntityType en_type, int health, int ammo, int score);
    uint32_t msg_code;
    int id;
    float x, y, w, h;
    int direction;
    AnimationType an_type;
    EntityType en_type;
    int health;
    int ammo;
    int score;

};

class Container {
public:
    enum class Type { SETUP = 0x00, GAME = 0x01 };

    // Game container constructor
    Container(uint32_t msg_code, int id, float x, float y, float w, float h, int direction,
              AnimationType an_type, EntityType en_type, int health, int ammo, int score);

    // Setup container constructor
    Container(uint32_t msg_code, const std::string& gameId, uint32_t maxPlayers,
              bool ok);

    Type type() const { return _type; }
    uint32_t code() const{return _code;};

    SetupContainer* setup_container;
    GameContainer* game_container;

private:
    uint32_t _code;
    Type _type;
};



#endif  // CONTAINER_H_
