#include "headers/model_updater.h"

#include "headers/client.h"
ModelUpdater::ModelUpdater(ClientProtocol& protocol, SdlWindow& window,
                           std::map<int, Entity*>& entidades, Queue<Container>& reciever_queue,
                           std::map<int, Player*>& personajes, UIManager& ui_manager, int id,
                           SoundManager& sound_manager, bool& gameStarted, bool& gameEnded):
        protocol(protocol),
        was_closed(false),
        entidades(entidades),
        reciever_queue(reciever_queue),
        personajes(personajes),
        ui_manager(ui_manager),
        sound_manager(sound_manager),
        id(id),
        gameStarted(gameStarted),
        gameEnded(gameEnded) {
    this->init_animations(window);
    // this->sound_manager.set_clientId(id);
}

void ModelUpdater::init_animations(SdlWindow& window) {
    this->animations[EntityType::JAZZ][AnimationType::WALK] =
            new Animation(new SdlTexture("../client_src/assets/textures/jazz_walking.png", window,
                                         Color{0x2C, 0x66, 0x96}),
                          8, AnimationSpeed::FAST);

    this->animations[EntityType::JAZZ][AnimationType::INTOXICATED_WALK] = new Animation(
            new SdlTexture("../client_src/assets/textures/jazz_intoxicated_walking.png", window,
                           Color{0x2C, 0x66, 0x96}),
            12, AnimationSpeed::FAST);

    this->animations[EntityType::JAZZ][AnimationType::INTOXICATED_IDLE] =
            new Animation(new SdlTexture("../client_src/assets/textures/jazz_intoxicated_idle.png",
                                         window, Color{0x2C, 0x66, 0x96}),
                          8, AnimationSpeed::DEFAULT);

    this->animations[EntityType::JAZZ][AnimationType::IDLE] =
            new Animation(new SdlTexture("../client_src/assets/textures/jazz_idle.png", window,
                                         Color{0x2C, 0x66, 0x96}),
                          13, AnimationSpeed::DEFAULT);

    this->animations[EntityType::JAZZ][AnimationType::SHOOT] =
            new Animation(new SdlTexture("../client_src/assets/textures/jazz_shooting.png", window,
                                         Color{0x2C, 0x66, 0x96}),
                          6, AnimationSpeed::FAST);

    this->animations[EntityType::JAZZ][AnimationType::SHOOT_IDLE] =
            new Animation(new SdlTexture("../client_src/assets/textures/jazz_shoot_idle.png",
                                         window, Color{0x2C, 0x66, 0x96}),
                          2, AnimationSpeed::SLOW);

    this->animations[EntityType::JAZZ][AnimationType::JUMP] =
            new Animation(new SdlTexture("../client_src/assets/textures/jazz_jumping.png", window,
                                         Color{0x2C, 0x66, 0x96}),
                          17, AnimationSpeed::FAST);

    this->animations[EntityType::JAZZ][AnimationType::FALL] =
            new Animation(new SdlTexture("../client_src/assets/textures/jazz_falling.png", window,
                                         Color{0x2C, 0x66, 0x96}),
                          3, AnimationSpeed::DEFAULT);

    this->animations[EntityType::JAZZ][AnimationType::SPECIAL_ACTION] =
            new Animation(new SdlTexture("../client_src/assets/textures/jazz_uppercut.png", window,
                                         Color{0x2C, 0x66, 0x96}),
                          12, AnimationSpeed::FAST);

    this->animations[EntityType::JAZZ][AnimationType::HURT] =
            new Animation(new SdlTexture("../client_src/assets/textures/jazz_hurt.png", window,
                                         Color{0x2C, 0x66, 0x96}),
                          9, AnimationSpeed::FAST);

    this->animations[EntityType::JAZZ][AnimationType::RUN] =
            new Animation(new SdlTexture("../client_src/assets/textures/jazz_running.png", window,
                                         Color{0x2C, 0x66, 0x96}),
                          8, AnimationSpeed::FAST);

    this->animations[EntityType::GHOST][AnimationType::WALK] =
            new Animation(new SdlTexture("../client_src/assets/textures/fantasma_walking.png",
                                         window, Color{0x2C, 0x66, 0x96}),
                          5, AnimationSpeed::FAST);

    this->animations[EntityType::BULLET][AnimationType::SHOOT] =
            new Animation(new SdlTexture("../client_src/assets/textures/bullet_shoot.png", window,
                                         Color{0x2C, 0x66, 0x96}),
                          6, AnimationSpeed::FAST);

    this->animations[EntityType::BULLET][AnimationType::PICKUP] =
            new Animation(new SdlTexture("../client_src/assets/textures/bullet_pickup.png", window,
                                         Color{0x2C, 0x66, 0x96}),
                          10, AnimationSpeed::FAST);

    this->animations[EntityType::ROCKET][AnimationType::SHOOT] =
            new Animation(new SdlTexture("../client_src/assets/textures/rocket_shoot.png", window,
                                         Color{0x2C, 0x66, 0x96}),
                          3, AnimationSpeed::FAST);

    this->animations[EntityType::ROCKET][AnimationType::PICKUP] =
            new Animation(new SdlTexture("../client_src/assets/textures/rocket_pickup.png", window,
                                         Color{0x2C, 0x66, 0x96}),
                          10, AnimationSpeed::FAST);

    this->animations[EntityType::ROCKET][AnimationType::EXPLOSION] =
            new Animation(new SdlTexture("../client_src/assets/textures/rocket_explosion.png",
                                         window, Color{0x2C, 0x66, 0x96}),
                          11, AnimationSpeed::FAST);

    this->animations[EntityType::ICE_BULLET][AnimationType::SHOOT] =
            new Animation(new SdlTexture("../client_src/assets/textures/rocket_explosion.png",
                                         window, Color{0x2C, 0x66, 0x96}),
                          11, AnimationSpeed::FAST);

    this->animations[EntityType::ICE_BULLET][AnimationType::PICKUP] =
            new Animation(new SdlTexture("../client_src/assets/textures/ice_bullet_pickup.png",
                                         window, Color{0x2C, 0x66, 0x96}),
                          5, AnimationSpeed::FAST);

    this->animations[EntityType::CARROT][AnimationType::PICKUP] =
            new Animation(new SdlTexture("../client_src/assets/textures/carrot_pickup.png", window,
                                         Color{0x2C, 0x66, 0x96}),
                          10, AnimationSpeed::DEFAULT);

    this->animations[EntityType::INTOXICATED_CARROT][AnimationType::PICKUP] = new Animation(
            new SdlTexture("../client_src/assets/textures/intoxicated_carrot_pickup.png", window,
                           Color{0x2C, 0x66, 0x96}),
            10, AnimationSpeed::DEFAULT);

    this->animations[EntityType::GOLD_COIN][AnimationType::PICKUP] =
            new Animation(new SdlTexture("../client_src/assets/textures/goldcoin_pickup.png",
                                         window, Color{0x2C, 0x66, 0x96}),
                          20, AnimationSpeed::FAST);

    this->animations[EntityType::GEM][AnimationType::PICKUP] =
            new Animation(new SdlTexture("../client_src/assets/textures/gem_pickup.png", window,
                                         Color{0x2C, 0x66, 0x96}),
                          8, AnimationSpeed::FAST);

    this->animations[EntityType::BAT][AnimationType::FLY] =
            new Animation(new SdlTexture("../client_src/assets/textures/bat_flying.png", window,
                                         Color{0x2C, 0x66, 0x96}),
                          8, AnimationSpeed::FAST);

    this->animations[EntityType::MONKEY][AnimationType::IDLE] =
            new Animation(new SdlTexture("../client_src/assets/textures/monkey_idle.png", window,
                                         Color{0x2C, 0x66, 0x96}),
                          12, AnimationSpeed::DEFAULT);

    this->animations[EntityType::MONKEY][AnimationType::SHOOT] =
            new Animation(new SdlTexture("../client_src/assets/textures/monkey_shoot.png", window,
                                         Color{0x2C, 0x66, 0x96}),
                          16, AnimationSpeed::DEFAULT);

    this->animations[EntityType::BANANA][AnimationType::WALK] =
            new Animation(new SdlTexture("../client_src/assets/textures/banana_shoot.png", window,
                                         Color{0x2C, 0x66, 0x96}),
                          8, AnimationSpeed::FAST);

    this->animations[EntityType::LORI][AnimationType::WALK] =
            new Animation(new SdlTexture("../client_src/assets/textures/lori_walking.png", window,
                                         Color{0x2C, 0x66, 0x96}),
                          8, AnimationSpeed::FAST);

    this->animations[EntityType::LORI][AnimationType::INTOXICATED_WALK] = new Animation(
            new SdlTexture("../client_src/assets/textures/lori_intoxicated_walking.png", window,
                           Color{0x2C, 0x66, 0x96}),
            12, AnimationSpeed::FAST);

    this->animations[EntityType::LORI][AnimationType::IDLE] =
            new Animation(new SdlTexture("../client_src/assets/textures/lori_idle.png", window,
                                         Color{0x2C, 0x66, 0x96}),
                          16, AnimationSpeed::FAST);

    this->animations[EntityType::LORI][AnimationType::INTOXICATED_IDLE] =
            new Animation(new SdlTexture("../client_src/assets/textures/lori_intoxicated_idle.png",
                                         window, Color{0x2C, 0x66, 0x96}),
                          12, AnimationSpeed::DEFAULT);

    this->animations[EntityType::LORI][AnimationType::SHOOT_IDLE] =
            new Animation(new SdlTexture("../client_src/assets/textures/lori_shoot_idle.png",
                                         window, Color{0x2C, 0x66, 0x96}),
                          2, AnimationSpeed::SLOW);

    this->animations[EntityType::LORI][AnimationType::SHOOT] =
            new Animation(new SdlTexture("../client_src/assets/textures/lori_shooting.png", window,
                                         Color{0x2C, 0x66, 0x96}),
                          4, AnimationSpeed::FAST);

    this->animations[EntityType::LORI][AnimationType::JUMP] =
            new Animation(new SdlTexture("../client_src/assets/textures/lori_jumping.png", window,
                                         Color{0x2C, 0x66, 0x96}),
                          18, AnimationSpeed::FAST);

    this->animations[EntityType::LORI][AnimationType::SPECIAL_ACTION] =
            new Animation(new SdlTexture("../client_src/assets/textures/lori_highkick.png", window,
                                         Color{0x2C, 0x66, 0x96}),
                          10, AnimationSpeed::FAST);

    this->animations[EntityType::LORI][AnimationType::HURT] =
            new Animation(new SdlTexture("../client_src/assets/textures/lori_hurt.png", window,
                                         Color{0x2C, 0x66, 0x96}),
                          11, AnimationSpeed::FAST);

    this->animations[EntityType::LORI][AnimationType::RUN] =
            new Animation(new SdlTexture("../client_src/assets/textures/lori_running.png", window,
                                         Color{0x2C, 0x66, 0x96}),
                          8, AnimationSpeed::FAST);

    this->animations[EntityType::SPAZ][AnimationType::WALK] =
            new Animation(new SdlTexture("../client_src/assets/textures/spaz_walking.png", window,
                                         Color{0x2C, 0x66, 0x96}),
                          8, AnimationSpeed::FAST);

    this->animations[EntityType::SPAZ][AnimationType::INTOXICATED_WALK] = new Animation(
            new SdlTexture("../client_src/assets/textures/spaz_intoxicated_walking.png", window,
                           Color{0x2C, 0x66, 0x96}),
            12, AnimationSpeed::FAST);

    this->animations[EntityType::SPAZ][AnimationType::IDLE] =
            new Animation(new SdlTexture("../client_src/assets/textures/spaz_idle.png", window,
                                         Color{0x2C, 0x66, 0x96}),
                          20, AnimationSpeed::FAST);

    this->animations[EntityType::SPAZ][AnimationType::INTOXICATED_IDLE] =
            new Animation(new SdlTexture("../client_src/assets/textures/spaz_intoxicated_idle.png",
                                         window, Color{0x2C, 0x66, 0x96}),
                          8, AnimationSpeed::DEFAULT);

    this->animations[EntityType::SPAZ][AnimationType::SHOOT_IDLE] =
            new Animation(new SdlTexture("../client_src/assets/textures/spaz_shoot_idle.png",
                                         window, Color{0x2C, 0x66, 0x96}),
                          2, AnimationSpeed::SLOW);

    this->animations[EntityType::SPAZ][AnimationType::SHOOT] =
            new Animation(new SdlTexture("../client_src/assets/textures/spaz_shooting.png", window,
                                         Color{0x2C, 0x66, 0x96}),
                          8, AnimationSpeed::FAST);

    this->animations[EntityType::SPAZ][AnimationType::JUMP] =
            new Animation(new SdlTexture("../client_src/assets/textures/spaz_jumping.png", window,
                                         Color{0x2C, 0x66, 0x96}),
                          17, AnimationSpeed::FAST);

    this->animations[EntityType::SPAZ][AnimationType::SPECIAL_ACTION] =
            new Animation(new SdlTexture("../client_src/assets/textures/spaz_sidekick.png", window,
                                         Color{0x2C, 0x66, 0x96}),
                          12, AnimationSpeed::FAST);

    this->animations[EntityType::SPAZ][AnimationType::HURT] =
            new Animation(new SdlTexture("../client_src/assets/textures/spaz_hurt.png", window,
                                         Color{0x2C, 0x66, 0x96}),
                          11, AnimationSpeed::FAST);

    this->animations[EntityType::SPAZ][AnimationType::RUN] =
            new Animation(new SdlTexture("../client_src/assets/textures/spaz_running.png", window,
                                         Color{0x2C, 0x66, 0x96}),
                          8, AnimationSpeed::FAST);
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
                c.game_container->score, c.game_container->name);
        personajes[c.game_container->id]->modify_animation(
                this->animations[c.game_container->en_type][c.game_container->an_type],
                c.game_container->an_type);
    } else {
        personajes[c.game_container->id] = new Player(
                c.game_container->id, c.game_container->x, c.game_container->y, c.game_container->w,
                c.game_container->h, c.game_container->direction, c.game_container->an_type,
                this->animations[c.game_container->en_type][c.game_container->an_type],
                c.game_container->en_type, c.game_container->health, c.game_container->ammo,
                c.game_container->score, c.game_container->name);
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

        if (c.sound_container != nullptr) {
            sound_manager.play_sound(c.sound_container->entity, c.sound_container->sound,
                                     c.sound_container->id);
            return;
        }

        switch (c.game_container->msg_code) {
            case 0:  // Actualiza un objeto, si no existe, lo crea.
                update_entity(c);
                break;

            case 1:  // Despawnea un objeto
                despawn_entity(c);
                break;

            case 2:  // Si el id es -1 o es igual al id del cliente se cierra el game del lado
                     // cliente
                if (c.game_container->id == -1 || c.game_container->id == id) {
                    gameEnded = true;
                }
                break;

            case 3:  // Actualiza un personaje, si no existe, lo crea.
                update_player(c);
                break;

            case 4:  // Actualiza el reloj de partida
                ui_manager.update_clock(c.game_container->id);
                break;
            case 5:  // Comienza la partida
                sound_manager.play_music();
                gameStarted = true;
                break;
            default:
                break;
        }

    } catch (const std::exception& e) {
        std::cerr << "Protocolo cerrado" << e.what() << "\n";
    }
}

// void ModelUpdater::set_clientId(int clientId) { this->sound_manager.set_clientId(clientId); }

bool ModelUpdater::is_running() { return not was_closed; }

void ModelUpdater::close() {
    this->reciever_queue.close();
    this->was_closed = true;
}
