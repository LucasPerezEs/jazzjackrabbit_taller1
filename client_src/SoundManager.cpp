#include "headers/SoundManager.h"

#include <iostream>

SoundManager::SoundManager(int clientId): clientId(clientId) { 
    this->init_sounds();
    this->init_music(); 
    }

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

//void SoundManager::set_clientId(int clientId) { this->clientId = clientId; }

void SoundManager::play_sound(EntityType entity, SoundType sound, int playerId) {
    std::cout << "entrando al sound manager\n";
    if (playerId != clientId) {
        return;  // En principio filtro todos los sonidos que no son del propio jugador.
    }

    std::cout << "el sonido es del cliente\n";
    sounds[entity][sound]->PlaySound();
    std::cout << "reproduciendo sonido\n";
}

void SoundManager::init_music() {
    music = new Music("../client_src/assets/music/Its_Pizza_Time.wav");
    music_volume = 20;
    music->SetVolume(music_volume);
}

void SoundManager::play_music() {
    music->PlayMusic(-1);
}

void SoundManager::stop_music() {
    music->PauseMusic();
}

void SoundManager::change_music_volume() {
    if (music_volume == 0) {
        music_volume = 20;
    }
    else {
        music_volume = 0;
    }
    music->SetVolume(music_volume);
}