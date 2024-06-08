#include "headers/entity.h"

int escalax = 26;
int escalay = 26;

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

void Entity::render(const SdlWindow& window, Entity* personaje, Camara *camara) {
    SDL_RendererFlip flip;
    if (direccion == -1) {
        flip = SDL_FLIP_HORIZONTAL;
    } else {
        flip = SDL_FLIP_NONE;
    }

    /*if (!camara->en_rango(this->x, this->y, this->width, this->height)) {
        return;
    }*/

    Area destArea(  (x - camara->x)*camara->escalax,
                    (camara->y - y - height)*camara->escalay,
                    width*camara->escalax,
                    height*camara->escalay);

    an->render(destArea, flip, current_frame);

    SDL_Rect r;
    r.h = height *camara->escalay;
    r.w = width *camara->escalax;
    r.x = (x - camara->x)*camara->escalax;
    r.y = (camara->y - y - height)*camara->escalay;
    SDL_RenderDrawRect(window.getRenderer(), &r);
}

std::pair<float, float> Entity::getPosition() {

    std::pair<float, float> posicionJugador;
    posicionJugador.first = this->x;
    posicionJugador.second = this->y;

    return posicionJugador;
}
