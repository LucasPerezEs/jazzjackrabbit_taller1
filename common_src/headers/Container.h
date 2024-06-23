#ifndef CONTAINER_H_
#define CONTAINER_H_

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "commands.h"
#include "entity_commands.h"
#include "protocol.h"
#include "sound_commands.h"


class SetupContainer {
public:
    SetupContainer(Setup::ActionType setupType, const std::string& gameId, uint32_t maxPlayers,
                   std::vector<uint32_t> cheats, bool ok);

    SetupContainer(Setup::ActionType setupType, std::vector<std::string>& gameList, bool ok);
    SetupContainer(Setup::ActionType setupType, std::vector<std::vector<std::string>>& mapReceived,
                   bool ok);
    SetupContainer(Setup::ActionType setupType, uint32_t id, bool ok);
    SetupContainer(Setup::ActionType setupType, bool ok);

    Setup::ActionType setupType;
    std::string gameId;
    uint32_t maxPlayers;
    std::vector<std::vector<std::string>> map;
    std::vector<uint32_t> cheats;
    std::vector<std::string> gameList;
    uint32_t clientId;
    bool ok;
};

class GameContainer {
public:
    GameContainer(uint32_t msg_code, int id, float x, float y, float w, float h, int direction,
                  AnimationType an_type, EntityType en_type, int health, AmmoData ammo, int score,
                  std::string name);

    // GameContainer(uint32_t msg_code, std::vector<std::uint32_t> score, std::vector<std::string>
    // names);

    uint32_t msg_code;
    int id;
    float x, y, w, h;
    int direction;
    AnimationType an_type;
    EntityType en_type;
    int health;
    AmmoData ammo;
    int score;
    std::string name;
};


class SoundContainer {
public:
    SoundContainer(EntityType entity, SoundType sound, int id);
    EntityType entity;
    SoundType sound;
    int id;
};


class Container {
public:
    enum class Type { SETUP = 0x00, GAME = 0x01, SOUND = 0x02 };

    // Game container constructor
    Container(uint32_t msg_code, int id, float x, float y, float w, float h, int direction,
              AnimationType an_type, EntityType en_type, int health, AmmoData ammo, int score,
              std::string name);

    // Container(uint32_t msg_code, std::vector<std::uint32_t> score, std::vector<std::string>
    // names);

    // Setup container constructor
    Container(Setup::ActionType setupType, const std::string& gameId, uint32_t maxPlayers,
              std::vector<uint32_t> cheats, bool ok);
    Container(Setup::ActionType setupType, std::vector<std::string>& gameList, bool ok);
    Container(Setup::ActionType setupType, uint32_t id, bool ok);

    // Sound container constructor
    Container(EntityType entity, SoundType sound, int id);

    // Setup map container
    Container(Setup::ActionType setupType, std::vector<std::vector<std::string>>& mapReceived,
              bool ok);

    // Setup confirmmation map saved
    Container(Setup::ActionType setupType, bool ok);


    Type type() const { return _type; }

    std::shared_ptr<SetupContainer> setup_container;
    std::shared_ptr<GameContainer> game_container;
    std::shared_ptr<SoundContainer> sound_container;
    // GameContainer* game_container;
    // SoundContainer* sound_container;

private:
    Type _type;
};


#endif  // CONTAINER_H_
