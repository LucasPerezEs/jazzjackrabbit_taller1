#ifndef CONTAINER_H_
#define CONTAINER_H_

#include <cstdint>
#include <string>
#include <vector>

#include "commands.h"
#include "entity_commands.h"


class SetupContainer {
public:
    SetupContainer(Setup::ActionType setupType, const std::string gameId, uint32_t maxPlayers,
                   bool ok);

    SetupContainer(Setup::ActionType setupType, std::vector<std::string> gameList, bool ok);

    Setup::ActionType setupType;
    std::string gameId;
    uint32_t maxPlayers;
    std::vector<std::string> gameList;
    bool ok;
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

    // Game container constructor./
    Container(uint32_t msg_code, int id, float x, float y, float w, float h, int direction,
              AnimationType an_type, EntityType en_type, int health, int ammo, int score);

    // Setup container constructor
    Container(Setup::ActionType setupType, const std::string gameId, uint32_t maxPlayers, bool ok);
    Container(Setup::ActionType setupType, std::vector<std::string> gameList, bool ok);

    Type type() const { return _type; }

    SetupContainer* setup_container;
    GameContainer* game_container;

private:
    Type _type;
};


#endif  // CONTAINER_H_
