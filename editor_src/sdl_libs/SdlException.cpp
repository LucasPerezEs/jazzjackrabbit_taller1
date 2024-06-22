#include "../headers/SdlException.h"

#include <string>

#include <SDL2/SDL.h>

SdlException::SdlException(const char* description):
        Exception("%s [%s]", description, SDL_GetError()) {}
