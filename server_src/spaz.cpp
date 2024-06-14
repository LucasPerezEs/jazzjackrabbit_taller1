#include "headers/spaz.h"

Spaz::Spaz(float x, float y, std::map<std::string, float>& config):
        Personaje(x, y, 2, 4, EntityType::SPAZ, AnimationType::SHOOT_IDLE, config),
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

void Spaz::check_colisions(Mapa& m, int aux_x, int aux_y) {

    bool colisionx;
    bool colisiony;
    colisionx = m.CheckColision(x, aux_y, width, height);
    colisiony = m.CheckColision(aux_x, y, width, height);

    if (colisionx) {  // si colisiona con la pos x actualizada
        x = aux_x;    // se pone la pos x anterior
        // width = auxw;  // lo mismo con la pos y
    }
    if (colisiony) {
        jumping = false;  // esta en el piso se puede saltar
        vely = 0;
        y = aux_y;
    }
    if (!(colisionx && colisiony)) {  // me fijo si justo se da el caso que solo choca en diagonal
        if (m.CheckColision(x, y, width, height)) {
            x = aux_x;  // se pone la pos x anterior
            // width = auxw;
        }
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
            x += velx * -1;  // se actualiza la posicin en x
            // width += velx * -1;
        }
        if (movingright) {
            x += velx;  // se actualiza la posicin en x
            // width += velx;
        }
    }
    y += vely;
    // height += vely;
    vely -= config["gravity"];  // esto es la aceleracion de la gravedad, se tiene que poner un
                                // limite de vely
}
