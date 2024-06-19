#ifndef SOUND_H
#define SOUND_H

#include <string>

#include <SDL2/SDL_mixer.h>

class Sound {
public:
    // Constructor: Loads a sound file
    explicit Sound(const std::string& filepath);

    // Destructor: Frees the sound resource
    ~Sound();

    // Plays the sound with specified number of loops (-1 for infinite loops)
    void PlaySound(int loops = 0);

    // Stops the sound playback
    void StopSound();

    // Sets the volume of the sound (0 to MIX_MAX_VOLUME)
    void SetVolume(int volume);

private:
    Mix_Chunk* m_chunk;  // Pointer to the loaded sound chunk
};

#endif  // SOUND_H
