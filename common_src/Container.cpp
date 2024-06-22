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
SetupContainer::SetupContainer(Setup::ActionType setupType, uint32_t id, bool ok):
        setupType(setupType), clientId(id), ok(ok) {}

// cppcheck-suppress uninitMemberVar
SetupContainer::SetupContainer(Setup::ActionType setupType, std::vector<std::vector<std::string>>& mapReceived, bool ok):
        setupType(setupType), map(mapReceived), ok(ok) {}


// GameContainer implementation
GameContainer::GameContainer(uint32_t msg_code, int id, float x, float y, float w, float h,
                             int direction, AnimationType an_type, EntityType en_type, int health,
                             int ammo, int score):
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
        score(score) {}


SoundContainer::SoundContainer(EntityType entity, SoundType sound, int id):
        entity(entity), sound(sound), id(id) {}

// Container implementation
Container::Container(uint32_t msg_code, int id, float x, float y, float w, float h, int direction,
                     AnimationType an_type, EntityType en_type, int health, int ammo, int score):
        setup_container(nullptr),
        game_container(new GameContainer(msg_code, id, x, y, w, h, direction, an_type, en_type,
                                         health, ammo, score)),
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
        // cppcheck-suppress noCopyConstructor
        // cppcheck-suppress noOperatorEq
        setup_container(new SetupContainer(setupType, id, ok)),
        game_container(nullptr),
        sound_container(nullptr),
        _type(Type::SETUP) {}

Container::Container(Setup::ActionType setupType, std::vector<std::vector<std::string>>& mapReceived, bool ok):
        // cppcheck-suppress noCopyConstructor
        // cppcheck-suppress noOperatorEq
        setup_container(new SetupContainer(setupType, mapReceived, ok)),
        game_container(nullptr),
        sound_container(nullptr),
        _type(Type::SETUP) {}

Container::Container(EntityType entity, SoundType sound, int id):
        setup_container(nullptr),
        game_container(nullptr),
        sound_container(new SoundContainer(entity, sound, id)),
        _type(Type::SOUND) {}

Container::~Container() {
       /* if (setup_container != nullptr) {
                delete setup_container;
        } 
        if (game_container != nullptr) {
                delete game_container;
        } 
        if (sound_container != nullptr) {
                delete sound_container;
        } */
}
