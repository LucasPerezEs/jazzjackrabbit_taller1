#include "../headers/spaz.h"

Spaz::Spaz(float x, float y, std::map<std::string, float>& config, Queue<Container>& q):
        Personaje(x, y, 2, 4, EntityType::SPAZ, AnimationType::SHOOT_IDLE, config, q),
        wait_sidekick(800) {}

void Spaz::special_action() {
    if (!special_action_active) {
        special_action_active = true;
        if (direccion == 1) {
            movingleft = false;
            movingright = true;
        } else {
            movingleft = true;
            movingright = false;
        }
        an_type = AnimationType::SPECIAL_ACTION;
        tiempo = std::chrono::system_clock::now();
    }
}

void Spaz::stop_special_action() {
    special_action_active = false;

    if (movingright) {
        stopMovingRight();
    } else {
        stopMovingLeft();
    }
}

void Spaz::update_position() {

    if (special_action_active && std::chrono::duration_cast<std::chrono::milliseconds>(
                                         std::chrono::system_clock::now() - tiempo)
                                                 .count() > wait_sidekick) {
        stop_special_action();
    }

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
    vely -= config["gravity"];  // esto es la aceleracion de la gravedad, se tiene que poner un
                                // limite de vely
}

void Spaz::check_special_action(bool col_x, bool col_y) {
    if (col_x && special_action_active) {
        stop_special_action();
    }
}
