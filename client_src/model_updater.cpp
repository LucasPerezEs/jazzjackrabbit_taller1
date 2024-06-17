#include "headers/model_updater.h"

#include "headers/client.h"
// cppcheck-suppress uninitMemberVar
ModelUpdater::ModelUpdater(ClientProtocol& protocol, SdlWindow& window,
                           std::map<int, Entity*>& entidades, Queue<Container>& reciever_queue,
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
            13, AnimationSpeed::DEFAULT);

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
                          3, AnimationSpeed::DEFAULT);

    this->animations[EntityType::JAZZ][AnimationType::SPECIAL_ACTION] =
            new Animation(new SdlTexture("../client_src/assets/jazz_uppercut.png", window,
                                         Color{0x2C, 0x66, 0x96}),
                          12, AnimationSpeed::FAST);

    this->animations[EntityType::JAZZ][AnimationType::HURT] = new Animation(
            new SdlTexture("../client_src/assets/jazz_hurt.png", window, Color{0x2C, 0x66, 0x96}),
            9, AnimationSpeed::FAST);

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
                          10, AnimationSpeed::DEFAULT);

    this->animations[EntityType::GOLD_COIN][AnimationType::PICKUP] =
            new Animation(new SdlTexture("../client_src/assets/goldcoin_pickup.png", window,
                                         Color{0x2C, 0x66, 0x96}),
                          20, AnimationSpeed::FAST);

    this->animations[EntityType::BAT][AnimationType::FLY] = new Animation(
            new SdlTexture("../client_src/assets/bat_flying.png", window, Color{0x2C, 0x66, 0x96}),
            8, AnimationSpeed::FAST);

    this->animations[EntityType::MONKEY][AnimationType::IDLE] = new Animation(
            new SdlTexture("../client_src/assets/monkey_idle.png", window, Color{0x2C, 0x66, 0x96}),
            12, AnimationSpeed::DEFAULT);

    this->animations[EntityType::MONKEY][AnimationType::SHOOT] =
            new Animation(new SdlTexture("../client_src/assets/monkey_shoot.png", window,
                                         Color{0x2C, 0x66, 0x96}),
                          16, AnimationSpeed::DEFAULT);

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

    this->animations[EntityType::LORI][AnimationType::HURT] = new Animation(
            new SdlTexture("../client_src/assets/lori_hurt.png", window, Color{0x2C, 0x66, 0x96}),
            11, AnimationSpeed::FAST);

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

    this->animations[EntityType::SPAZ][AnimationType::HURT] = new Animation(
            new SdlTexture("../client_src/assets/spaz_hurt.png", window, Color{0x2C, 0x66, 0x96}),
            11, AnimationSpeed::FAST);
}

void ModelUpdater::run() {
    while (this->is_running()) {
        this->update(FRAME_RATE);
    }
}

void ModelUpdater::update_entity(Container& c) {

    if (entidades.count(c.game_container->id) > 0) {
        entidades[c.game_container->id]->update_stats(c.game_container->x, c.game_container->y,
                                                      c.game_container->w, c.game_container->h,
                                                      c.game_container->direction);
        entidades[c.game_container->id]->modify_animation(
                this->animations[c.game_container->en_type][c.game_container->an_type],
                c.game_container->an_type);
    } else {
        entidades[c.game_container->id] = new Entity(
                c.game_container->id, c.game_container->x, c.game_container->y, c.game_container->w,
                c.game_container->h, c.game_container->direction, c.game_container->an_type,
                this->animations[c.game_container->en_type][c.game_container->an_type],
                c.game_container->en_type);
    }
}

void ModelUpdater::update_player(Container& c) {
    if (personajes.count(c.game_container->id) > 0) {
        personajes[c.game_container->id]->update_player_stats(
                c.game_container->x, c.game_container->y, c.game_container->w, c.game_container->h,
                c.game_container->direction, c.game_container->health, c.game_container->ammo,
                c.game_container->score);
        personajes[c.game_container->id]->modify_animation(
                this->animations[c.game_container->en_type][c.game_container->an_type],
                c.game_container->an_type);
    } else {
        personajes[c.game_container->id] = new Player(
                c.game_container->id, c.game_container->x, c.game_container->y, c.game_container->w,
                c.game_container->h, c.game_container->direction, c.game_container->an_type,
                this->animations[c.game_container->en_type][c.game_container->an_type],
                c.game_container->en_type, c.game_container->health, c.game_container->ammo,
                c.game_container->score);
    }
}

void ModelUpdater::despawn_entity(Container& c) {
    if (personajes.count(c.game_container->id) > 0) {
        personajes.erase(c.game_container->id);
    } else {
        entidades.erase(c.game_container->id);
    }
}

void ModelUpdater::update(float dt) {

    try {

        Container c = this->reciever_queue.pop();


        switch (c.game_container->msg_code) {
            case 0:  // Actualiza un objeto, si no existe, lo crea.
                update_entity(c);
                break;

            case 1:  // Despawnea un objeto
                despawn_entity(c);
                break;

            case 2:  // Setea el ID al cliente, si todavia no fue seteado
                if (cliente->get_id() == -1) {
                    cliente->set_id(c.game_container->id);
                }
                break;

            case 3:  // Actualiza un personaje, si no existe, lo crea.
                update_player(c);
                break;

            case 4:  // Actualiza el reloj de partida
                ui_manager.update_clock(c.game_container->id);
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
