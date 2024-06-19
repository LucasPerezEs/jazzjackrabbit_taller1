#include "../headers/Music.h"

#include <iostream>

Music::Music(std::string musicfilepath) {

    // Load our music file
    m_music = Mix_LoadMUS(musicfilepath.c_str());
    if (!m_music) {
        printf("Mix_LoadMUS error: %s\n", Mix_GetError());
    }
}

Music::~Music() {
    if (m_music) {
        Mix_FreeMusic(m_music);
    }
}

/// number of times to play the music
/// 0 means 0
/// -1 means plays forever.
void Music::PlayMusic(int loops) {
    if (m_music != nullptr) {
        Mix_PlayMusic(m_music, loops);
    }
}

void Music::PauseMusic() { Mix_PauseMusic(); }

// A range of 0 to 128
void Music::SetVolume(int volume) { Mix_VolumeMusic(volume); }
