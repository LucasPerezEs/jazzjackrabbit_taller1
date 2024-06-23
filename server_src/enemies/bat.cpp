#include "../headers/bat.h"

Bat::Bat(float x, float y, std::map<std::string, float>& config):
        Enemigo(x, y, 2, 2, config["bat_life"], config["bat_speed"], config["bat_damage"],
                config["bat_prob_carrot"], config["bat_prob_ammo"], config["bat_prob_goldcoin"],
                config["ghost_prob_rocket"], EntityType::BAT, AnimationType::FLY, config) {
    lim_y_sup = y + 20;  // cuanto se va a mover de izquierda a derecha
    lim_y_inf = y - 20;
}

void Bat::update(Mapa& m, ListaObjetos& objetos, Queue<Container>& q) {
    float auxx = x;
    float auxy = y;  // se guarda la posicion actual
    bool colisiony;

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
        if (contador == 1) {  // si acaba de morir dropea una municion o moneda o zanahoria
            drop_item(objetos, q);
        }
        if (contador == 240) {  // despues de un rato revive
            vida = max_life;
            borrar = false;
            objetos.agregar_objeto(e);
            contador = 0;
            Container c(0, this->id, this->x, this->y, this->width, this->height, this->direccion,
                        AnimationType::FLY, EntityType::BAT, 0, {EntityType::NONE_ENTITY, 0}, 0,
                        "");
            q.try_push(c);
        }
        contador++;
    }
}
