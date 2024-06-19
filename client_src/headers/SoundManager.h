#ifndef SOUND_MANAGER_H
#define SOUND_MANAGER_H

#include <map>

#include "../../common_src/headers/entity_commands.h"
#include "../../common_src/headers/sound_commands.h"

#include "Sound.h"

class SoundManager {

private:
    std::map<EntityType, std::map<SoundType, Sound*>> sounds;
    int clientId;

public:
    SoundManager();

    void init_sounds();

    void play_sound(EntityType entity, SoundType sound, int playerId);

    void set_clientId(int clientId);
};

#endif
