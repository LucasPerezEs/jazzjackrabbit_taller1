#include "../headers/ghost.h"

Ghost::Ghost(float x, float y, std::map<std::string, float>& config):
        Enemigo(x, y, 2, 4, config["ghost_life"], config["ghost_speed"], config["ghost_damage"],
                config["ghost_prob_carrot"], config["ghost_prob_ammo"],
                config["ghost_prob_goldcoin"], config["ghost_prob_rocket"],
                config["ghost_prob_gem"], EntityType::GHOST, AnimationType::WALK, config) {
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
                this->an_type, this->en_type, 0, {EntityType::NONE_ENTITY, 0}, 0, "");
    q.try_push(c);
}

void Ghost::update_vivo(ListaObjetos& objetos, Queue<Container>& q,
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
            objetos.agregar_objeto(e);
            // contador = 0;
            Container c(0, this->id, this->x, this->y, this->width, this->height, this->direccion,
                        AnimationType::WALK, EntityType::GHOST, 0, {EntityType::NONE_ENTITY, 0}, 0,
                        "");
            q.try_push(c);
        }
        // contador++;
    }
}
