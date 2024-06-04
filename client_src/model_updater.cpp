#include "headers/model_updater.h"
#include "headers/client.h"

ModelUpdater::ModelUpdater(ClientProtocol& protocol, SdlWindow& window,
                           std::map<int, Entity*>& entidades, Queue<Contenedor>& reciever_queue):
        protocol(protocol),
        was_closed(false),
        entidades(entidades),
        reciever_queue(reciever_queue) {
    this->init_animations(window);
}

void ModelUpdater::init_animations(SdlWindow& window) {
    this->animations[EntityType::JAZZ][AnimationType::WALK] =
            new Animation(new SdlTexture("../client_src/assets/jazz_walking.png", window,
                                         Color{0x2C, 0x66, 0x96}),
                          8);
    this->animations[EntityType::JAZZ][AnimationType::INTOXICATED_WALK] =
            new Animation(new SdlTexture("../client_src/assets/jazz_intoxicated_walking.png",
                                         window, Color{0x2C, 0x66, 0x96}),
                          12);
    this->animations[EntityType::ENEMY][AnimationType::WALK] =
            new Animation(new SdlTexture("../client_src/assets/fantasma_walking.png", window,
                                         Color{0x2C, 0x66, 0x96}),
                          5);
    this->animations[EntityType::BULLET][AnimationType::WALK] =
            new Animation(new SdlTexture("../client_src/assets/bullet_shoot.png", window,
                                         Color{0x2C, 0x66, 0x96}),
                          6);
    this->animations[EntityType::BULLET][AnimationType::PICKUP] =
            new Animation(new SdlTexture("../client_src/assets/bullet_pickup.png", window,
                                         Color{0x2C, 0x66, 0x96}),
                          10);
}

void ModelUpdater::run() {
    while (this->is_running()) {
        this->update(FRAME_RATE);
    }
}

void ModelUpdater::update(float dt) {

    try {

        Contenedor c = this->reciever_queue.pop();

        switch (c.msg_code()) {
            case 0:  // Actualiza un objeto, si no existe, lo crea.
                if (entidades.count(c.id()) > 0) {
                    entidades[c.id()]->update_stats(c.posx(), c.posy(), c.width(), c.height(),
                                                    c.direccion());
                    entidades[c.id()]->modify_animation(
                            this->animations[c.entity_type()][c.animation_type()],
                            c.animation_type());
                } else {
                    entidades[c.id()] = new Entity(
                            c.id(), c.posx(), c.posy(), c.width(), c.height(), c.direccion(),
                            c.animation_type(),
                            this->animations[c.entity_type()][c.animation_type()], c.entity_type());
                }
                break;

            case 1:  // Despawnea un objeto
                entidades.erase(c.id());
                break;

            case 2:  // Despawnea un objeto
                cliente->set_id(c.id());
                break;

            default:
                break;
        }

    } catch (const std::exception& e) {
        std::cerr << "Protocolo cerrado" << e.what() << "\n";
    }
}

bool ModelUpdater::is_running() { return not was_closed; }

void ModelUpdater::agregar_cliente(Client* c) {
    this->cliente = c;
}

void ModelUpdater::close() {
    this->reciever_queue.close();
    this->was_closed = true;
}
