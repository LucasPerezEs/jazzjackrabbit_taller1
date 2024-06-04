#include "headers/entity.h"

int escalax = 24;
int escalay = 18;

Entity::Entity(int id, float x, float y, float width, float height, int direccion,
               AnimationType an_type, Animation* an, EntityType entity_type):
        id(id),
        x(x),
        y(y),
        width(width),
        height(height),
        direccion(direccion),
        an_type(an_type),
        an(an),
        entity_type(entity_type),
        current_frame(0) {}

void Entity::update_stats(float new_x, float new_y, float new_width, float new_height,
                          int new_direccion) {
    this->x = new_x;
    this->y = new_y;
    this->width = new_width;
    this->height = new_height;
    this->direccion = new_direccion;
}

void Entity::modify_animation(Animation* new_an, AnimationType new_an_type) {
    if (this->an_type == new_an_type) {
        return;
    }
    new_an->reset();
    this->an_type = new_an_type;
    this->an = new_an;
}

void Entity::update_animation() { this->current_frame = an->update(current_frame); }

void Entity::render(const SdlWindow& window) {
    SDL_RendererFlip flip;
    if (direccion == -1) {
        flip = SDL_FLIP_HORIZONTAL;
    } else {
        flip = SDL_FLIP_NONE;
    }

    //int render_width = (this->width - this->x) * 40;
    //int render_height = (this->height - this->y) * 30;

    Area destArea(x*escalax, 600-y*escalay-(this->height - this->y) * escalay, (this->width - this->x)*escalax, (this->height - this->y) * escalay);

    an->render(destArea, flip, current_frame);

    SDL_Rect r;
    r.h = ((this->y - this->height) * escalay);
    r.w = ((this->width - this->x) * escalax);
    r.x = this->x * escalax;
    r.y = 600 - (this->y * escalay);
    SDL_RenderDrawRect(window.getRenderer(), &r);    
}

std::pair<float, float> Entity::getPosition() {

    std::pair<float, float> posicionJugador;
    posicionJugador.first = this->x;
    posicionJugador.second = this->y;

    return posicionJugador;
}
