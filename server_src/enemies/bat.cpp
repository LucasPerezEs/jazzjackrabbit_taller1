#include "../headers/bat.h"

Bat::Bat(float x, float y, std::map<std::string, float>& config):
        Enemigo(x, y, 2, 2, config["bat_life"], config["bat_speed"], config["bat_damage"],
                config["bat_prob_carrot"], config["bat_prob_ammo"], config["bat_prob_goldcoin"],
                config["bat_prob_rocket"], config["bat_prob_gem"], config["bat_prob_icebullet"],
                EntityType::BAT, AnimationType::FLY, config) {
    lim_y_sup = y + 20;  // cuanto se va a mover de izquierda a derecha
    lim_y_inf = y - 20;
}

void Bat::update(Mapa& m, ListaObjetos& objetos, Queue<Container>& q) {
    float auxx = x;
    float auxy = y;  // se guarda la posicion actual
    bool colisiony;

    check_frozen();

    if (frozen) {
        return;
    }

    y += speed * direccion;

    colisiony = m.CheckColision(auxx, y, width, height);

    if (colisiony || y > lim_y_sup || y < lim_y_inf) {
        direccion = direccion * -1;
        y = auxy;
    }

    Container c(0, this->id, this->x, this->y, this->width, this->height, this->direccion,
                this->an_type, this->en_type, 0, {EntityType::NONE_ENTITY, 0}, 0, "");
    q.try_push(c);
}

void Bat::update_vivo(ListaObjetos& objetos, Queue<Container>& q,
                      std::map<uint32_t, std::shared_ptr<Personaje>>& clientCharacters,
                      std::shared_ptr<Ente> e) {
    if (vida <= 0) {
        if (!killed) {  // si acaba de morir dropea una municion o moneda o zanahoria
            killed = true;
            last_killed = std::chrono::system_clock::now();
            drop_item(objetos, q);
        } else if (std::chrono::duration_cast<std::chrono::milliseconds>(
                           std::chrono::system_clock::now() - last_killed)
                           .count() >= 3000) {  // despues de un rato revive
            killed = false;
            vida = max_life;
            borrar = false;
            frozen = false;
            objetos.agregar_objeto(e);
            // contador = 0;
            Container c(0, this->id, this->x, this->y, this->width, this->height, this->direccion,
                        AnimationType::FLY, EntityType::BAT, 0, {EntityType::NONE_ENTITY, 0}, 0,
                        "");
            q.try_push(c);
        }
        // contador++;
    }
}
