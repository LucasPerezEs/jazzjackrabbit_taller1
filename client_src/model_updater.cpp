#include "headers/model_updater.h"

#include "headers/client.h"
// cppcheck-suppress uninitMemberVar
ModelUpdater::ModelUpdater(ClientProtocol& protocol, SdlWindow& window,
                           std::map<int, Entity*>& entidades, Queue<Contenedor>& reciever_queue,
                           std::map<int, Player*>& personajes, UIManager& ui_manager):
        protocol(protocol),
        was_closed(false),
        entidades(entidades),
        reciever_queue(reciever_queue),
        personajes(personajes),
        ui_manager(ui_manager) {
    this->init_animations(window);
}

void ModelUpdater::init_animations(SdlWindow& window) {
    this->animations[EntityType::JAZZ][AnimationType::WALK] =
            new Animation(new SdlTexture("../client_src/assets/jazz_walking.png", window,
                                         Color{0x2C, 0x66, 0x96}),
                          8, AnimationSpeed::FAST);

    this->animations[EntityType::JAZZ][AnimationType::INTOXICATED_WALK] =
            new Animation(new SdlTexture("../client_src/assets/jazz_intoxicated_walking.png",
                                         window, Color{0x2C, 0x66, 0x96}),
                          12, AnimationSpeed::FAST);

    this->animations[EntityType::JAZZ][AnimationType::IDLE] = new Animation(
            new SdlTexture("../client_src/assets/jazz_idle.png", window, Color{0x2C, 0x66, 0x96}),
            13, AnimationSpeed::NORMAL);

    this->animations[EntityType::JAZZ][AnimationType::SHOOT] =
            new Animation(new SdlTexture("../client_src/assets/jazz_shooting.png", window,
                                         Color{0x2C, 0x66, 0x96}),
                          6, AnimationSpeed::FAST);

    this->animations[EntityType::JAZZ][AnimationType::SHOOT_IDLE] =
            new Animation(new SdlTexture("../client_src/assets/jazz_shoot_idle.png", window,
                                         Color{0x2C, 0x66, 0x96}),
                          2, AnimationSpeed::SLOW);

    this->animations[EntityType::JAZZ][AnimationType::JUMP] =
            new Animation(new SdlTexture("../client_src/assets/jazz_jumping.png", window,
                                         Color{0x2C, 0x66, 0x96}),
                          17, AnimationSpeed::FAST);

    this->animations[EntityType::JAZZ][AnimationType::FALL] =
            new Animation(new SdlTexture("../client_src/assets/jazz_falling.png", window,
                                         Color{0x2C, 0x66, 0x96}),
                          3, AnimationSpeed::NORMAL);

    this->animations[EntityType::JAZZ][AnimationType::SPECIAL_ACTION] =
            new Animation(new SdlTexture("../client_src/assets/jazz_uppercut.png", window,
                                         Color{0x2C, 0x66, 0x96}),
                          12, AnimationSpeed::FAST);

    this->animations[EntityType::GHOST][AnimationType::WALK] =
            new Animation(new SdlTexture("../client_src/assets/fantasma_walking.png", window,
                                         Color{0x2C, 0x66, 0x96}),
                          5, AnimationSpeed::FAST);

    this->animations[EntityType::BULLET][AnimationType::WALK] =
            new Animation(new SdlTexture("../client_src/assets/bullet_shoot.png", window,
                                         Color{0x2C, 0x66, 0x96}),
                          6, AnimationSpeed::FAST);

    this->animations[EntityType::BULLET][AnimationType::PICKUP] =
            new Animation(new SdlTexture("../client_src/assets/bullet_pickup.png", window,
                                         Color{0x2C, 0x66, 0x96}),
                          10, AnimationSpeed::FAST);

    this->animations[EntityType::CARROT][AnimationType::PICKUP] =
            new Animation(new SdlTexture("../client_src/assets/carrot_pickup.png", window,
                                         Color{0x2C, 0x66, 0x96}),
                          10, AnimationSpeed::NORMAL);

    this->animations[EntityType::GOLD_COIN][AnimationType::PICKUP] =
            new Animation(new SdlTexture("../client_src/assets/goldcoin_pickup.png", window,
                                         Color{0x2C, 0x66, 0x96}),
                          20, AnimationSpeed::FAST);

    this->animations[EntityType::BAT][AnimationType::FLY] = new Animation(
            new SdlTexture("../client_src/assets/bat_flying.png", window, Color{0x2C, 0x66, 0x96}),
            8, AnimationSpeed::FAST);

    this->animations[EntityType::MONKEY][AnimationType::IDLE] = new Animation(
            new SdlTexture("../client_src/assets/monkey_idle.png", window, Color{0x2C, 0x66, 0x96}),
            12, AnimationSpeed::NORMAL);

    this->animations[EntityType::MONKEY][AnimationType::SHOOT] =
            new Animation(new SdlTexture("../client_src/assets/monkey_shoot.png", window,
                                         Color{0x2C, 0x66, 0x96}),
                          16, AnimationSpeed::NORMAL);

    this->animations[EntityType::BANANA][AnimationType::WALK] =
            new Animation(new SdlTexture("../client_src/assets/banana_shoot.png", window,
                                         Color{0x2C, 0x66, 0x96}),
                          8, AnimationSpeed::FAST);

    this->animations[EntityType::LORI][AnimationType::WALK] =
            new Animation(new SdlTexture("../client_src/assets/lori_walking.png", window,
                                         Color{0x2C, 0x66, 0x96}),
                          8, AnimationSpeed::FAST);

    this->animations[EntityType::LORI][AnimationType::IDLE] = new Animation(
            new SdlTexture("../client_src/assets/lori_idle.png", window, Color{0x2C, 0x66, 0x96}),
            16, AnimationSpeed::FAST);

    this->animations[EntityType::LORI][AnimationType::SHOOT_IDLE] =
            new Animation(new SdlTexture("../client_src/assets/lori_shoot_idle.png", window,
                                         Color{0x2C, 0x66, 0x96}),
                          2, AnimationSpeed::SLOW);

    this->animations[EntityType::LORI][AnimationType::SHOOT] =
            new Animation(new SdlTexture("../client_src/assets/lori_shooting.png", window,
                                         Color{0x2C, 0x66, 0x96}),
                          4, AnimationSpeed::FAST);

    this->animations[EntityType::LORI][AnimationType::JUMP] =
            new Animation(new SdlTexture("../client_src/assets/lori_jumping.png", window,
                                         Color{0x2C, 0x66, 0x96}),
                          18, AnimationSpeed::FAST);

    this->animations[EntityType::LORI][AnimationType::SPECIAL_ACTION] =
            new Animation(new SdlTexture("../client_src/assets/lori_highkick.png", window,
                                         Color{0x2C, 0x66, 0x96}),
                          10, AnimationSpeed::FAST);

    this->animations[EntityType::SPAZ][AnimationType::WALK] =
            new Animation(new SdlTexture("../client_src/assets/spaz_walking.png", window,
                                         Color{0x2C, 0x66, 0x96}),
                          8, AnimationSpeed::FAST);

    this->animations[EntityType::SPAZ][AnimationType::IDLE] = new Animation(
            new SdlTexture("../client_src/assets/spaz_idle.png", window, Color{0x2C, 0x66, 0x96}),
            20, AnimationSpeed::FAST);

    this->animations[EntityType::SPAZ][AnimationType::SHOOT_IDLE] =
            new Animation(new SdlTexture("../client_src/assets/spaz_shoot_idle.png", window,
                                         Color{0x2C, 0x66, 0x96}),
                          2, AnimationSpeed::SLOW);

    this->animations[EntityType::SPAZ][AnimationType::SHOOT] =
            new Animation(new SdlTexture("../client_src/assets/spaz_shooting.png", window,
                                         Color{0x2C, 0x66, 0x96}),
                          8, AnimationSpeed::FAST);

    this->animations[EntityType::SPAZ][AnimationType::JUMP] =
            new Animation(new SdlTexture("../client_src/assets/spaz_jumping.png", window,
                                         Color{0x2C, 0x66, 0x96}),
                          17, AnimationSpeed::FAST);

    this->animations[EntityType::SPAZ][AnimationType::SPECIAL_ACTION] =
            new Animation(new SdlTexture("../client_src/assets/spaz_sidekick.png", window,
                                         Color{0x2C, 0x66, 0x96}),
                          12, AnimationSpeed::FAST);
}

void ModelUpdater::run() {
    while (this->is_running()) {
        this->update(FRAME_RATE);
    }
}

void ModelUpdater::update_entity(Contenedor& c) {
    if (entidades.count(c.id()) > 0) {
        entidades[c.id()]->update_stats(c.posx(), c.posy(), c.width(), c.height(), c.direccion());
        entidades[c.id()]->modify_animation(this->animations[c.entity_type()][c.animation_type()],
                                            c.animation_type());
    } else {
        entidades[c.id()] =
                new Entity(c.id(), c.posx(), c.posy(), c.width(), c.height(), c.direccion(),
                           c.animation_type(),
                           this->animations[c.entity_type()][c.animation_type()], c.entity_type());
    }
}

void ModelUpdater::update_player(Contenedor& c) {
    if (personajes.count(c.id()) > 0) {
        personajes[c.id()]->update_player_stats(c.posx(), c.posy(), c.width(), c.height(),
                                                c.direccion(), c.vida(), c.municion(), c.score());
        personajes[c.id()]->modify_animation(this->animations[c.entity_type()][c.animation_type()],
                                             c.animation_type());
    } else {
        personajes[c.id()] = new Player(c.id(), c.posx(), c.posy(), c.width(), c.height(),
                                        c.direccion(), c.animation_type(),
                                        this->animations[c.entity_type()][c.animation_type()],
                                        c.entity_type(), c.vida(), c.municion(), c.score());
    }
}

void ModelUpdater::despawn_entity(Contenedor& c) {
    if (personajes.count(c.id()) > 0) {
        personajes.erase(c.id());
    } else {
        entidades.erase(c.id());
    }
}

void ModelUpdater::update(float dt) {

    try {

        Contenedor c = this->reciever_queue.pop();


        switch (c.msg_code()) {
            case 0:  // Actualiza un objeto, si no existe, lo crea.
                update_entity(c);
                break;

            case 1:  // Despawnea un objeto
                despawn_entity(c);
                break;

            case 2:  // Setea el ID al cliente
                cliente->set_id(c.id());
                break;

            case 3:  // Actualiza un personaje, si no existe, lo crea.
                update_player(c);
                break;

            case 4:  // Actualiza el reloj de partida
                ui_manager.update_clock(c.id());
                break;

            default:
                break;
        }

    } catch (const std::exception& e) {
        std::cerr << "Protocolo cerrado" << e.what() << "\n";
    }
}

bool ModelUpdater::is_running() { return not was_closed; }

void ModelUpdater::agregar_cliente(Client* c) { this->cliente = c; }

void ModelUpdater::close() {
    this->reciever_queue.close();
    this->was_closed = true;
}
