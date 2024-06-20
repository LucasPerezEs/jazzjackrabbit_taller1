#ifndef SOUND_MANAGER_H
#define SOUND_MANAGER_H

#include <map>

#include "../../common_src/headers/entity_commands.h"
#include "../../common_src/headers/sound_commands.h"

#include "Music.h"
#include "Sound.h"

class SoundManager {

private:
    std::map<EntityType, std::map<SoundType, Sound*>> sounds;
    int clientId;
    Music* music;
    int music_volume;

public:
    explicit SoundManager(int clientId);

    void init_music();

    void play_music();

    void change_music_volume();

    void init_sounds();

    void play_sound(EntityType entity, SoundType sound, int playerId);

    // void set_clientId(int clientId);
};

#endif
