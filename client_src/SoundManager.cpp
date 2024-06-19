#include "headers/SoundManager.h"

#include <iostream>

SoundManager::SoundManager(): clientId(-1) { this->init_sounds(); }

void SoundManager::init_sounds() {
    this->sounds[JAZZ][JUMP_SOUND] = new Sound("../client_src/assets/music/jazz_jump_sound.wav");
    this->sounds[JAZZ][RUN_SOUND] = new Sound("../client_src/assets/music/run_sound.wav");
    this->sounds[JAZZ][HURT1_SOUND] = new Sound("../client_src/assets/music/jazz_hurt_sound.wav");
    this->sounds[JAZZ][HURT2_SOUND] = new Sound("../client_src/assets/music/jazz_hurt2_sound.wav");

    this->sounds[LORI][JUMP_SOUND] = new Sound("../client_src/assets/music/lori_jump_sound.wav");
    this->sounds[LORI][RUN_SOUND] = new Sound("../client_src/assets/music/run_sound.wav");
    this->sounds[LORI][HURT1_SOUND] = new Sound("../client_src/assets/music/lori_hurt_sound.wav");
    this->sounds[LORI][HURT2_SOUND] = new Sound("../client_src/assets/music/lori_hurt2_sound.wav");

    this->sounds[SPAZ][JUMP_SOUND] = new Sound("../client_src/assets/music/spaz_jump_sound.wav");
    this->sounds[SPAZ][RUN_SOUND] = new Sound("../client_src/assets/music/run_sound.wav");
    this->sounds[SPAZ][HURT1_SOUND] = new Sound("../client_src/assets/music/spaz_hurt_sound.wav");
    this->sounds[SPAZ][HURT2_SOUND] = new Sound("../client_src/assets/music/spaz_hurt2_sound.wav");

    this->sounds[BULLET][SHOT_SOUND] = new Sound("../client_src/assets/music/bullet_sound.wav");

    this->sounds[GOLD_COIN][PICKUP_SOUND] =
            new Sound("../client_src/assets/music/goldcoin_sound.wav");
    this->sounds[BULLET][PICKUP_SOUND] = new Sound("../client_src/assets/music/ammo_sound.wav");
}

void SoundManager::set_clientId(int clientId) { this->clientId = clientId; }

void SoundManager::play_sound(EntityType entity, SoundType sound, int playerId) {
    if (playerId != clientId) {
        return;  // En principio filtro todos los sonidos que no son del propio jugador.
    }

    sounds[entity][sound]->PlaySound();
}
