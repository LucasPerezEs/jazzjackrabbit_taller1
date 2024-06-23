#include "../headers/personaje.h"

#include <cmath>
#include <iostream>
#include <map>

#include "../headers/bullet.h"
#include "../headers/projectile.h"
#include "../headers/rocket.h"

Personaje::Personaje(float x, float y, float w, float h, EntityType en_type, AnimationType an_type,
                     // cppcheck-suppress passedByValue
                     std::map<std::string, float>& config, Queue<Container>& q, std::string name):
        Ente(x, y, w, h, config["player_life"], en_type, an_type),
        tiempo(std::chrono::system_clock::now()),
        last_hurt(std::chrono::system_clock::now()),
        config(config),
        arma(config),
        state(PlayerState::NORMAL),
        q(q),
        name(name) {
    velx = config["player_speed"];
    jump_speed = config["player_jump"];
    danio_ataque_especial = config["player_special_attack_dmg"];
    vely = 0;
    direccion = 1;
    jumping = false;
    movingright = false;
    movingleft = false;
    disparando = false;
    special_action_active = false;
    contador = 0;
    municion = 20;
    espera_idle = 2000;  // en milisegundos
    espera_shoot = 250;  // Misma que la del arma
    espera_hurt =
            1000;  // Cuando el personaje es atacado, se debe esperar 1s para volver a recibir danio
    score = 0;
    direccion_movimientox = 1;
    direccion_movimientoy = 0;
    killed_by_id = -1;
}

void Personaje::moveRigth() {
    if (special_action_active || state == PlayerState::HURTED) {
        return;
    }

    movingright = true;
    direccion = 1;

    if (state == PlayerState::INTOXICATED) {
        an_type = AnimationType::INTOXICATED_WALK;
    } else {
        an_type = AnimationType::WALK;
    }

    tiempo = std::chrono::system_clock::now();
}
void Personaje::moveLeft() {
    if (special_action_active || state == PlayerState::HURTED) {
        return;
    }
    movingleft = true;
    direccion = -1;

    if (state == PlayerState::INTOXICATED) {
        an_type = AnimationType::INTOXICATED_WALK;
    } else {
        an_type = AnimationType::WALK;
    }

    tiempo = std::chrono::system_clock::now();
}
void Personaje::stopMovingRight() {
    movingright = false;
    if (!jumping && !special_action_active && state == PlayerState::HURTED) {
        an_type = AnimationType::SHOOT_IDLE;
    }
}

void Personaje::stopMovingLeft() {
    movingleft = false;
    if (!jumping && !special_action_active && state == PlayerState::HURTED) {
        an_type = AnimationType::SHOOT_IDLE;
    }
}

void Personaje::run() {
    if (state == PlayerState::HURTED) {
        return;
    }

    velx = config["player_run_speed"];
    an_type = AnimationType::RUN;
    Container c(this->en_type, SoundType::RUN_SOUND, id);
    q.try_push(c);
    // an_type = AnimationType::RUN;
}

void Personaje::stoprunning() {
    velx = config["player_speed"];
    if (!jumping && !special_action_active && state == PlayerState::HURTED) {
        an_type = AnimationType::SHOOT_IDLE;
    }
}

void Personaje::jump() {
    if (!jumping && !special_action_active &&
        state != PlayerState::HURTED) {  // Esto es para evitar que se pueda spamear el jump y volar
        vely = config["player_jump"];
        jumping = true;
        an_type = AnimationType::JUMP;
        tiempo = std::chrono::system_clock::now();

        Container c(this->en_type, SoundType::JUMP_SOUND, id);
        q.try_push(c);
    }
}

bool Personaje::has_special_action_active() { return special_action_active; }

void Personaje::add_score(int score) {
    this->score += score;
    std::cout << "Puntos: " << this->score << std::endl;
}

void Personaje::check_idle() {

    if (state == PlayerState::INTOXICATED) {
        auto now = std::chrono::system_clock::now();
        auto duration =
                std::chrono::duration_cast<std::chrono::seconds>(now - intoxicated_start).count();

        if (duration >= 10) {
            state = PlayerState::NORMAL;
        }
    }

    if (state == PlayerState::HURTED && std::chrono::duration_cast<std::chrono::milliseconds>(
                                                std::chrono::system_clock::now() - last_hurt)
                                                        .count() > espera_hurt / 2) {
        state = PlayerState::NORMAL;
    }

    if (!movingleft && !movingright && !disparando && state != PlayerState::HURTED && !jumping &&
        std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() -
                                                              tiempo)
                        .count() > espera_idle) {

        if (state == PlayerState::INTOXICATED) {
            an_type = AnimationType::INTOXICATED_IDLE;
        } else {
            an_type = AnimationType::IDLE;
        }

    } else if (!movingleft && !movingright && state != PlayerState::HURTED && !jumping &&
               std::chrono::duration_cast<std::chrono::milliseconds>(
                       std::chrono::system_clock::now() - tiempo)
                               .count() > espera_shoot) {
        an_type = AnimationType::SHOOT_IDLE;
    }
}

void Personaje::update_position() {

    if (!(movingleft && movingright) &&
        (movingleft || movingright)) {  // mientras se este apretando una tecla de mover el jugador
        if (movingleft) {
            x += velx * -1 * direccion_movimientox;
            y += velx * -1 * direccion_movimientoy;  // se actualiza la posicin en x
        }
        if (movingright) {
            x += velx * direccion_movimientox;  // se actualiza la posicin en x
            y += velx * direccion_movimientoy;
        }
    }
    y += vely;
    // height += vely;
    vely -= config["gravity"];  // esto es la aceleracion de la gravedad, se tiene que poner un
                                // limite de vely
}

void Personaje::check_colisions(Mapa& m, float aux_x, float aux_y) {

    bool colisionx = false;
    bool colisiony = false;
    bool colisiondiagonal = false;
    // float x_modificado = x;
    // float y_modificado = y;
    for (auto diagonal: m.diagonalesDer) {

        if (diagonal->x <= x + width && x + width <= diagonal->x + diagonal->w &&
            y <= diagonal->y + diagonal->h - (diagonal->x + diagonal->w - (x + width)) &&
            diagonal->y + diagonal->h - (diagonal->x + diagonal->w - (x + width)) <=
                    y + height / 2) {
            jumping = false;
            vely = 0;
            y = diagonal->y + diagonal->h - (diagonal->x + diagonal->w - (x + width));
            // special_action_active = false;
            colisiony = true;
            colisionx = true;
            direccion_movimientox = sqrt(2) / 2;
            direccion_movimientoy = 1;
            colisiondiagonal = true;
        } else {
            if (aux_x < (diagonal->x + diagonal->w) && (aux_x + width) > diagonal->x &&
                (y + 2 * height / 3) < diagonal->y && diagonal->y < y + height) {
                vely = 0;
                y = diagonal->y - height;
                // special_action_active = false;
                colisiony = true;
            }
            if (x < (diagonal->x + diagonal->w) && (diagonal->x + diagonal->w) < x + width / 2 &&
                aux_y < (diagonal->y + diagonal->h) && (aux_y + height) > diagonal->y) {
                x = diagonal->x + diagonal->w;
                colisionx = true;
            }
            if (x < diagonal->x + diagonal->w && diagonal->x + diagonal->w < x + width &&
                y < diagonal->y + diagonal->h && diagonal->y + diagonal->h < y + height) {
                y = diagonal->y + diagonal->h;
                vely = 0;
                colisiony = true;
            }
        }
    }

    for (auto diagonal: m.diagonalesIzq) {

        if (diagonal->x <= x && x <= diagonal->x + diagonal->w &&
            y <= diagonal->y + diagonal->h - (x - diagonal->x) &&
            diagonal->y + diagonal->h - (x - diagonal->x) <= y + height / 2) {
            jumping = false;
            vely = 0;
            y = diagonal->y + diagonal->h - (x - diagonal->x);
            // special_action_active = false;
            colisiony = true;
            colisionx = true;
            direccion_movimientox = sqrt(2) / 2;
            direccion_movimientoy = -1;
            colisiondiagonal = true;
        } else {
            if (aux_x < (diagonal->x + diagonal->w) && (aux_x + width) > diagonal->x &&
                (y + 2 * height / 3) < diagonal->y && diagonal->y < y + height) {
                vely = 0;
                y = diagonal->y - height;
                // special_action_active = false;
                colisiony = true;
            }
            if (x + width / 2 < diagonal->x && diagonal->x < x + width &&
                aux_y < (diagonal->y + diagonal->h) && (aux_y + height) > diagonal->y) {
                x = diagonal->x - width;
                colisionx = true;
            }
            if (x < diagonal->x && diagonal->x < x + width && y < diagonal->y + diagonal->h &&
                diagonal->y + diagonal->h < y + height) {
                y = diagonal->y + diagonal->h;
                vely = 0;
                colisiony = true;
            }
        }
    }

    if (!colisiondiagonal) {
        direccion_movimientox = 1;
        direccion_movimientoy = 0;
    }

    for (auto terreno: m.objetos) {
        if (aux_x < (terreno->x + terreno->w) && (aux_x + width) > terreno->x &&
            (y + 2 * height / 3) < (terreno->y + terreno->h) && (y + height) > terreno->y) {
            vely = 0;
            y = terreno->y - height;
            // special_action_active = false;
            colisiony = true;
        } else if (aux_x < (terreno->x + terreno->w) && (aux_x + width) > terreno->x &&
                   y < (terreno->y + terreno->h) && (y + height / 4) > terreno->y) {
            jumping = false;
            vely = 0;
            y = terreno->y + terreno->h;
            // special_action_active = false;
            colisiony = true;
        }

        if (x < (terreno->x + terreno->w) && (x + width / 2) > terreno->x &&
            aux_y < (terreno->y + terreno->h) && (aux_y + height) > terreno->y) {
            x = terreno->x + terreno->w;
            colisionx = true;
        } else if ((x + width / 2) < (terreno->x + terreno->w) && (x + width) > terreno->x &&
                   aux_y < (terreno->y + terreno->h) && (aux_y + height) > terreno->y) {
            x = terreno->x - width;
            colisionx = true;
        }
    }

    check_special_action(colisionx, colisiony);

    if (!(colisionx && colisiony)) {  // me fijo si justo se da el caso que solo choca en diagonal
        if (m.CheckColision(x, y, width, height)) {
            x = aux_x;  // se pone la pos x anterior
        }
    }

    // Caso que salta mientras se mueve y no suelta el boton
    if ((colisiondiagonal || colisiony || colisionx) && an_type == AnimationType::JUMP) {
        an_type = AnimationType::WALK;
    }
}

void Personaje::update(Mapa& m, ListaObjetos& objetos, Queue<Container>& q) {
    if (disparando) {
        disparar(objetos);  // Creo que ahora con sender y receiver esto se puede poner afuera
    }

    float aux_x = x;
    float aux_y = y;  // se guarda la posicion actual

    check_idle();

    update_position();

    check_colisions(m, aux_x, aux_y);

    AmmoData ammo = {this->arma.selected_ammo(), this->arma.remaining_ammo()};

    Container c(3, this->id, this->x, this->y, this->width, this->height, this->direccion,
                this->an_type, this->en_type, this->vida, ammo, this->score, this->name);
    q.try_push(c);
}

void Personaje::update_vivo(ListaObjetos& objetos, Queue<Container>& q,
                            std::unordered_map<uint32_t, Personaje*>& clientCharacters) {
    if (vida <= 0) {
        // Me acaban de matar
        if (contador == 0) {
            if (killed_by_id != -1) {
                Personaje* killer = clientCharacters[killed_by_id];
                if (killer) {
                    std::cout << "Killer id: " << killer->id << std::endl;
                    killer->add_score(this->score);
                }
            }
        }

        if (contador ==
            240) {  // revive despues de tantos ciclos y lo agrego al vector de colisiones
            vida = config["player_life"];
            borrar = false;
            killed_by_id = -1;
            score = 0;
            objetos.agregar_objeto(this);
            contador = -1;
            AmmoData ammo = {this->arma.selected_ammo(), this->arma.remaining_ammo()};
            Container c(3, this->id, this->x, this->y, this->width, this->height, this->direccion,
                        this->an_type, this->en_type, this->vida, ammo, this->score, this->name);
            q.try_push(c);
        }
        contador++;
    }
}

void Personaje::colision(ZanahoriaEnvenenada& ze) {

    this->state = PlayerState::INTOXICATED;
    this->tiempo = std::chrono::system_clock::now();
    this->intoxicated_start = std::chrono::system_clock::now();
}


void Personaje::colision(Objeto& o) {
    if (check_colision(o)) {
        o.colision(*this);
    }
}
void Personaje::colision(Enemigo& e) {
    if (special_action_active) {
        e.RecibirDanio(danio_ataque_especial);

    } else if (std::chrono::duration_cast<std::chrono::milliseconds>(
                       std::chrono::system_clock::now() - last_hurt)
                       .count() > espera_hurt) {
        RecibirDanio(e.get_damage());
        if (state != PlayerState::INTOXICATED) {
            state = PlayerState::HURTED;
        }
        an_type = AnimationType::HURT;
        last_hurt = std::chrono::system_clock::now();
        tiempo = std::chrono::system_clock::now();
        Container c(en_type, SoundType::HURT1_SOUND, id);
        q.try_push(c);
    }
}

void Personaje::colision(Banana& b) {  // Banana y Bala deberian pertenecer a clase 'Proyectil'
    if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() -
                                                              last_hurt)
                .count() > espera_hurt) {

        if (state != PlayerState::INTOXICATED) {
            state = PlayerState::HURTED;
        }
        an_type = AnimationType::HURT;
        last_hurt = std::chrono::system_clock::now();
        tiempo = std::chrono::system_clock::now();
        RecibirDanio(b.danio);
        b.borrar = true;
        Container c(en_type, SoundType::HURT2_SOUND, id);
        q.try_push(c);
    }
}

void Personaje::colision(Projectile& b) {
    if (b.get_shooter_id() == this->id) {
        return;
    }

    if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() -
                                                              last_hurt)
                .count() > espera_hurt) {

        if (state != PlayerState::INTOXICATED) {
            state = PlayerState::HURTED;
        }

        an_type = AnimationType::HURT;
        last_hurt = std::chrono::system_clock::now();
        tiempo = std::chrono::system_clock::now();
        RecibirDanio(b.danio);
        b.borrar = true;
        Container c(en_type, SoundType::HURT1_SOUND, id);
        q.try_push(c);
    }

    check_dead(b.get_shooter_id());
}

void Personaje::colision(Municion& m) { m.colision(*this); }

void Personaje::colision(Personaje& p) {
    if (p.has_special_action_active()) {
        RecibirDanio(p.danio_ataque_especial);
        Container c(en_type, SoundType::HURT2_SOUND, id);
        q.try_push(c);
        check_dead(p.id);
    } else if (this->special_action_active) {
        p.RecibirDanio(danio_ataque_especial);
        p.check_dead(this->id);
    }
}

void Personaje::check_dead(int killer_id) {
    if (vida <= 0) {
        killed_by_id = killer_id;  // Me guardo el id de quien me mato
        std::cout << "Me mato: " << killed_by_id << std::endl;
    }
}

void Personaje::disparar(ListaObjetos& objetos) {

    if (state == PlayerState::INTOXICATED) {
        return;
    }

    if (arma.disparar(objetos, id, x, width, y, height, direccion, q)) {
        tiempo = std::chrono::system_clock::now();
        if (!movingleft && !movingright) {
            an_type = AnimationType::SHOOT;
        }
    }
}

void Personaje::set_id(uint32_t i) { id = i; }

void Personaje::change_selected_ammo() {
    if (arma.change_selected_ammo()) {
        Container c(EntityType::NONE_ENTITY, SoundType::CHANGE_AMMO, id);
        q.try_push(c);
    } else {
        Container c(EntityType::NONE_ENTITY, SoundType::NO_AMMO, id);
        q.try_push(c);
    }
}

void Personaje::add_ammo(EntityType ammo, int n) { arma.add_ammo(ammo, n); }


Arma::Arma(std::map<std::string, float>& config):
        config(config), tiempo(std::chrono::system_clock::now()), current_ammo(0) {
    init_ammo();
}

void Arma::init_ammo() {
    this->ammo_types.insert(ammo_types.end(), EntityType::BULLET);
    this->ammo_types.insert(ammo_types.end(), EntityType::ROCKET);

    this->ammo_inventory[EntityType::BULLET] = config["bullet_initial_ammo"];
    this->ammo_inventory[EntityType::ROCKET] = config["rocket_initial_ammo"];

    this->fire_rates[EntityType::BULLET] = 1000 / config["bullet_firerate"];
    this->fire_rates[EntityType::ROCKET] = 1000 / config["rocket_firerate"];
}

void Arma::add_ammo(EntityType ammo, int n) { ammo_inventory[ammo] += n; }

bool Arma::change_selected_ammo() {
    bool changed_ammo = false;
    int i = (current_ammo + 1) % ammo_types.size();
    while (i != current_ammo) {

        if (ammo_inventory[ammo_types[i]] > 0) {
            current_ammo = i;
            changed_ammo = true;
            tiempo = std::chrono::system_clock::now();
            break;
        }

        i = (i + 1) % ammo_types.size();
    }

    return changed_ammo;
}

EntityType Arma::selected_ammo() { return ammo_types[current_ammo]; }

int Arma::remaining_ammo() { return ammo_inventory[ammo_types[current_ammo]]; }

void Arma::spawn_projectile(ListaObjetos& objetos, EntityType ammo, int x, int y, int d,
                            int shooter_id, std::map<std::string, float>& config) {
    switch (ammo) {
        case BULLET: {
            Bullet* b = new Bullet(x, y, d, shooter_id, config);
            objetos.agregar_objeto(b);
            break;
        }

        case ROCKET: {
            Rocket* b = new Rocket(x, y, d, shooter_id, config);
            objetos.agregar_objeto(b);
            break;
        }

        default:
            break;
    }
}

bool Arma::disparar(ListaObjetos& objetos, int shooter_id, float x, float w, float y, float h,
                    int d, Queue<Container>& q) {

    EntityType current_ammo_type = ammo_types[current_ammo];
    int current_firerate = fire_rates[current_ammo_type];


    if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() -
                                                              tiempo)
                .count() > current_firerate) {

        tiempo = std::chrono::system_clock::now();

        if (ammo_inventory[current_ammo_type] <= 0) {
            Container c(EntityType::NONE_ENTITY, SoundType::NO_AMMO, shooter_id);
            q.try_push(c);
            return false;
        }

        int aux;
        if (d ==
            1) {  // Si se dispara mirando a la derecha la bala sale desde la derecha del objeto
            aux = x + w;  // Si se dispara mirando a la izquierda sale a la izquierda
        } else {
            aux = x;
        }

        Container c(current_ammo_type, SoundType::SHOT_SOUND, shooter_id);
        q.try_push(c);

        spawn_projectile(objetos, current_ammo_type, aux, y + h / 2, d, shooter_id, config);

        ammo_inventory[current_ammo_type] -= 1;
        return true;
    }

    return false;
}
