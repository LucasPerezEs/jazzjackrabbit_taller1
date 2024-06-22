#include "../headers/Sound.h"

#include <iostream>

Sound::Sound(const std::string& filepath) {
    // Load the WAV file into the Mix_Chunk
    m_chunk = Mix_LoadWAV(filepath.c_str());
    if (!m_chunk) {
        std::cerr << "Mix_LoadWAV error: " << Mix_GetError() << std::endl;
    }
}

Sound::~Sound() {
    // Free the sound chunk if it was loaded
    if (m_chunk) {
        Mix_FreeChunk(m_chunk);
    }
}

void Sound::PlaySound(int loops) {
    if (m_chunk != nullptr) {
        // Play the sound on the first available channel
        if (Mix_PlayChannel(-1, m_chunk, loops) == -1) {
            std::cerr << "Mix_PlayChannel error: " << Mix_GetError() << std::endl;
        }
    }
}

void Sound::StopSound() {
    // Halt all currently playing channels
    Mix_HaltChannel(-1);
}

void Sound::SetVolume(int volume) {
    // Set the volume for the sound chunk
    Mix_VolumeChunk(m_chunk, volume);
}
