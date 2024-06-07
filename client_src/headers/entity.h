#ifndef ENTITY_H_
#define ENTITY_H_

#include <iostream>
#include <utility>

#include <SDL2/SDL.h>

#include "../../common_src/headers/entity_commands.h"

#include "Animation.h"
#include "SdlTexture.h"
#include "SdlWindow.h"
#include "camara.h"

class Entity {
private:
    int id;
    float x;
    float y;
    float width;
    float height;
    int direccion;
    // int vida;
    AnimationType an_type;
    Animation* an;
    EntityType entity_type;
    int current_frame;  // Como hay un 'banco' de animaciones, las entidades pueden compartir una
    int speed_counter;  // misma animacion. entonces cada entidad debe llevar en que frame esta de
                        // la animacion y su contador de velocidad.

public:
    Entity(int id, float x, float y, float width, float height, int direccion,
           AnimationType an_type, Animation* an, EntityType entity_type);

    void update_stats(float x, float y, float width, float height, int direccion);
    void modify_animation(Animation* new_an, AnimationType an_type);
    void update_animation();
    // void recibir_danio(int d);
    // bool vivo();
    // virtual void eliminar();
    void render(const SdlWindow& window, Entity* personaje, Camara *camara);
    std::pair<float, float> getPosition();
};

#endif
