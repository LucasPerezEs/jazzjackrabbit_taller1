#ifndef ENTITY_H_
#define ENTITY_H_

#include <SDL2/SDL.h>

#include "Animation.h"
#include "SdlTexture.h"
#include "SdlWindow.h"
#include "texture_ids.h"

class Entity {
private:
    int id;
    float x;
    float y;
    float width;
    float height;
    bool borrar;
    /*int direccion;
    int vida;
    Animation an;
    EntityType entity_type;*/

public:
    Entity(int id, float x, float y, float width, float height, bool borrar);

    void update_stats(float x, float y, float width, float height, bool borrar);
    // void update_animation(float dt);
    // void recibir_danio(int d);
    // bool vivo();
    // virtual void eliminar();
    void render(const SdlWindow& window);
    // void change_animation(SdlTexture* texture, int n_frames);
};

#endif
