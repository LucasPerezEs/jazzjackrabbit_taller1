#include "headers/Container.h"

#include <iostream>


// SetupContainer implementation
// cppcheck-suppress uninitMemberVar
SetupContainer::SetupContainer(Setup::ActionType setupType, const std::string& gameId,
                               // cppcheck-suppress passedByValue
                               uint32_t maxPlayers, std::vector<uint32_t> cheats, bool ok):
        setupType(setupType), gameId(gameId), maxPlayers(maxPlayers), cheats(cheats), ok(ok) {}

// cppcheck-suppress uninitMemberVar
SetupContainer::SetupContainer(Setup::ActionType setupType, std::vector<std::string>& gameList,
                               bool ok):
        setupType(setupType), gameList(gameList), ok(ok) {}

// cppcheck-suppress uninitMemberVar
SetupContainer::SetupContainer(Setup::ActionType setupType, bool ok):
        setupType(setupType), ok(ok) {}

// cppcheck-suppress uninitMemberVar
SetupContainer::SetupContainer(Setup::ActionType setupType, uint32_t id, bool ok):
        setupType(setupType), clientId(id), ok(ok) {}

// cppcheck-suppress uninitMemberVar
SetupContainer::SetupContainer(Setup::ActionType setupType,
                               std::vector<std::vector<std::string>>& mapReceived, bool ok):
        setupType(setupType), map(mapReceived), ok(ok) {}


// cppcheck-suppress uninitMemberVar
SetupContainer::SetupContainer(Setup::ActionType setupType, const std::string& gameId,
                               // cppcheck-suppress passedByValue
                               uint32_t maxPlayers, const std::string& mapName, std::vector<uint32_t> cheats, bool ok):
        setupType(setupType), gameId(gameId), maxPlayers(maxPlayers), mapName(mapName), cheats(cheats), ok(ok) {}


// GameContainer implementation
GameContainer::GameContainer(uint32_t msg_code, int id, float x, float y, float w, float h,
                             int direction, AnimationType an_type, EntityType en_type, int health,
                             // cppcheck-suppress passedByValue
                             AmmoData ammo, int score, std::string name):
        msg_code(msg_code),
        id(id),
        x(x),
        y(y),
        w(w),
        h(h),
        direction(direction),
        an_type(an_type),
        en_type(en_type),
        health(health),
        ammo(ammo),
        score(score),
        name(name) {}

/*GameContainer::GameContainer(uint32_t msg_code, std::vector<std::uint32_t> score,
 * std::vector<std::string> names): score(score), names(names) {}*/

SoundContainer::SoundContainer(EntityType entity, SoundType sound, int id):
        entity(entity), sound(sound), id(id) {}

// Container implementation
Container::Container(uint32_t msg_code, int id, float x, float y, float w, float h, int direction,
                     AnimationType an_type, EntityType en_type, int health, AmmoData ammo,
                     // cppcheck-suppress passedByValue
                     int score, std::string name):
        setup_container(nullptr),
        game_container(new GameContainer(msg_code, id, x, y, w, h, direction, an_type, en_type,
                                         health, ammo, score, name)),
        sound_container(nullptr),
        _type(Type::GAME) {}

Container::Container(Setup::ActionType setupType, const std::string& gameId, uint32_t maxPlayers,
                     // cppcheck-suppress passedByValue
                     std::vector<uint32_t> cheats, bool ok):
        setup_container(new SetupContainer(setupType, gameId, maxPlayers, cheats, ok)),
        game_container(nullptr),
        sound_container(nullptr),
        _type(Type::SETUP) {}

Container::Container(Setup::ActionType setupType, std::vector<std::string>& gameList, bool ok):
        setup_container(new SetupContainer(setupType, gameList, ok)),
        game_container(nullptr),
        sound_container(nullptr),
        _type(Type::SETUP) {}

Container::Container(Setup::ActionType setupType, uint32_t id, bool ok):
        setup_container(new SetupContainer(setupType, id, ok)),
        game_container(nullptr),
        sound_container(nullptr),
        _type(Type::SETUP) {}


Container::Container(Setup::ActionType setupType,
                     std::vector<std::vector<std::string>>& mapReceived, bool ok):
        setup_container(new SetupContainer(setupType, mapReceived, ok)),
        game_container(nullptr),
        sound_container(nullptr),
        _type(Type::SETUP) {}

Container::Container(Setup::ActionType setupType, const std::string& gameId, uint32_t maxPlayers, const std::string& mapName,
                     // cppcheck-suppress passedByValue
                     std::vector<uint32_t> cheats, bool ok):
        setup_container(new SetupContainer(setupType, gameId, maxPlayers, mapName, cheats, ok)),
        game_container(nullptr),
        sound_container(nullptr),
        _type(Type::SETUP) {}

Container::Container(Setup::ActionType setupType, bool ok):
        setup_container(new SetupContainer(setupType, ok)),
        game_container(nullptr),
        sound_container(nullptr),
        _type(Type::SETUP) {}

Container::Container(EntityType entity, SoundType sound, int id):
        setup_container(nullptr),
        game_container(nullptr),
        sound_container(new SoundContainer(entity, sound, id)),
        _type(Type::SOUND) {}


