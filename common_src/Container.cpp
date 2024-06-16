#include "headers/Container.h"

// SetupContainer implementation
SetupContainer::SetupContainer(uint32_t msg_code, const std::string& gameId, uint32_t maxPlayers,
                               bool ok):
        _gameId(gameId), _maxPlayers(maxPlayers), _ok(ok) {}

std::string SetupContainer::gameId() const { return _gameId; }

uint32_t SetupContainer::maxPlayers() const { return _maxPlayers; }

bool SetupContainer::ok() const { return _ok; }

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


// Container implementation
Container::Container(uint32_t msg_code, int id, float x, float y, float w, float h, int direction,
                     AnimationType an_type, EntityType en_type, int health, int ammo, int score):
        setup_container(nullptr),
        game_container(new GameContainer(msg_code, id, x, y, w, h, direction, an_type, en_type,
                                         health, ammo, score)),
        _code(msg_code),
        _type(Type::GAME) {}

Container::Container(uint32_t msg_code, const std::string& gameId, uint32_t maxPlayers, bool ok):
        setup_container(new SetupContainer(msg_code, gameId, maxPlayers, ok)),
        game_container(nullptr),
        _code(msg_code),
        _type(Type::SETUP) {}
