#include "../headers/SdlWindow.h"

#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include "../headers/SdlException.h"


SdlWindow::SdlWindow(int width, int height): width(width), height(height) {
    int errCode = SDL_Init(SDL_INIT_VIDEO);
    if (errCode) {
        throw SdlException("Error en la inicialización");
    }
    errCode = SDL_CreateWindowAndRenderer(width, height, SDL_RENDERER_ACCELERATED, &this->window,
                                          &this->renderer);
    if (errCode) {
        throw SdlException("Error al crear ventana");
    }
}


SdlWindow::~SdlWindow() {
    std::cout << "Destruyendo" << std::endl;
    if (this->renderer) {
        SDL_DestroyRenderer(this->renderer);
        this->renderer = nullptr;
    }

    if (this->window) {
        SDL_DestroyWindow(this->window);
        this->window = nullptr;
    }
}

void SdlWindow::fill(int r, int g, int b, int alpha) {
    SDL_SetRenderDrawColor(this->renderer, r, g, b, alpha);
    SDL_RenderClear(this->renderer);
}


//ANTES: void SdlWindow::fill() { this->fill(0x33, 0x33, 0x33, 0xFF); }
//AHORA:
void SdlWindow::fill() { this->fill(255, 255, 255, 255); }

void SdlWindow::render() { SDL_RenderPresent(this->renderer); }


SDL_Renderer* SdlWindow::getRenderer() const { return this->renderer; }
