#include "../headers/ghost.h"

Ghost::Ghost(float x, float y, std::map<std::string, float>& config):
        Enemigo(x, y, 2, 4, config["ghost_life"], config["ghost_speed"], config["ghost_damage"],
                config["ghost_prob_carrot"], config["ghost_prob_ammo"],
                config["ghost_prob_goldcoin"], config["ghost_prob_rocket"], EntityType::GHOST,
                AnimationType::WALK, config) {
    lim_x_der = x + 20;  // cuanto se va a mover de izquierda a derecha
    lim_x_izq = x - 20;
    lim_y = y + 0;  // por si lo queremos hacer volador
}

void Ghost::update(Mapa& m, ListaObjetos& objetos, Queue<Container>& q) {
    float auxx = x;
    float auxy = y;  // se guarda la posicion actual
    // float auxw = width;
    // float auxh = height;
    bool colisionx;

    x += speed * direccion;
    // width += 0.25 * direccion;

    colisionx = m.CheckColision(x, auxy, width, height);

    if (colisionx || x > lim_x_der || x < lim_x_izq) {
        direccion = direccion * -1;  // si colisiona con la pos x actualizada
        x = auxx;                    // se pone la pos x anterior
        // width = auxw;
    }
    Container c(0, this->id, this->x, this->y, this->width, this->height, this->direccion,
                this->an_type, this->en_type, 0, 0, 0, "");
    q.try_push(c);
}

void Ghost::update_vivo(ListaObjetos& objetos, Queue<Container>& q,
                        std::unordered_map<uint32_t, Personaje*>& clientCharacters) {
    if (vida <= 0) {
        if (contador == 1) {  // si acaba de morir dropea una municion o moneda o zanahoria
            drop_item(objetos, q);
        }
        if (contador == 240) {  // despues de un rato revive
            vida = max_life;
            borrar = false;
            objetos.agregar_objeto(this);
            contador = 0;
            Container c(0, this->id, this->x, this->y, this->width, this->height, this->direccion,
                        AnimationType::WALK, EntityType::GHOST, 0, 0, 0, "");
            q.try_push(c);
        }
        contador++;
    }
}
