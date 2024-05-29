#include "headers/entity.h"

Entity::Entity(int id, float x, float y, float width, float height, bool borrar):
        id(id), x(x), y(y), width(width), height(height), borrar(borrar) {}

void Entity::update_stats(float new_x, float new_y, float new_width, float new_height,
                          bool new_borrar) {
    this->x = new_x;
    this->y = new_y;
    this->width = new_width;
    this->height = new_height;
    this->borrar = new_borrar;
}

void Entity::render(const SdlWindow& window) {
    SDL_Rect r;
    r.h = ((this->y - this->height) * 6);
    r.w = ((this->width - this->x) * 8);
    r.x = this->x * 8;
    r.y = 600 - (this->y * 6);
    SDL_RenderDrawRect(window.getRenderer(), &r);
}
