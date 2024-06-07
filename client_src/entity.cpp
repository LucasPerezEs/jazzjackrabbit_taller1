#include "headers/entity.h"

int escalax = 16;
int escalay = 12;

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
        current_frame(0),
        speed_counter(1) {}

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

    this->current_frame = 0;
    this->speed_counter = 1;
    this->an_type = new_an_type;
    this->an = new_an;
}

void Entity::update_animation() { this->current_frame = an->update(current_frame, speed_counter); }

void Entity::render(const SdlWindow& window, Entity* personaje) {
    SDL_RendererFlip flip;
    if (direccion == -1) {
        flip = SDL_FLIP_HORIZONTAL;
    } else {
        flip = SDL_FLIP_NONE;
    }

    // int render_width = (this->width - this->x) * 40;
    // int render_height = (this->height - this->y) * 30;

    Area destArea(x * escalax - personaje->getPosition().first * escalax + 400,
                  600 - y * escalay - (this->height) * escalay +
                          personaje->getPosition().second * escalay - 2 * escalay,
                  (this->width) * escalax, (this->height) * escalay);

    an->render(destArea, flip, current_frame);

    SDL_Rect r;
    r.h = (this->height * escalay);
    r.w = (this->width * escalax);
    r.x = this->x * escalax - personaje->getPosition().first * escalax + 400;
    r.y = 600 - (this->y * escalay) + personaje->getPosition().second * escalay - 2 * escalay-(this->height * escalay);
    SDL_RenderDrawRect(window.getRenderer(), &r);
}

std::pair<float, float> Entity::getPosition() {

    std::pair<float, float> posicionJugador;
    posicionJugador.first = this->x;
    posicionJugador.second = this->y;

    return posicionJugador;
}
