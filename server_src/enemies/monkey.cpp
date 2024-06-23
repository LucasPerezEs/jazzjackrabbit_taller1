#include "../headers/monkey.h"

Monkey::Monkey(float x, float y, std::map<std::string, float>& config):
        Enemigo(x, y, 4, 6, config["monkey_life"], config["monkey_speed"], config["monkey_damage"],
                config["monkey_prob_carrot"], config["monkey_prob_ammo"],
                config["monkey_prob_goldcoin"], config["ghost_prob_rocket"], EntityType::MONKEY,
                AnimationType::IDLE, config),
        tiempo(std::chrono::system_clock::now()) {
    wait_idle = 3000;  // 3 segs
    wait_throw = 1000;
    throwing_banana = false;
    direccion = -1;
}

void Monkey::update(Mapa& m, ListaObjetos& objetos, Queue<Container>& q) {

    if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() -
                                                              tiempo)
                        .count() > wait_idle &&
        !throwing_banana) {
        this->an_type = AnimationType::SHOOT;
        this->throwing_banana = true;
    }

    if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() -
                                                              tiempo)
                .count() > wait_idle + wait_throw) {
        throw_banana(objetos);
    }

    Container c(0, this->id, this->x, this->y, this->width, this->height, this->direccion,
                this->an_type, this->en_type, 0, {EntityType::NONE_ENTITY, 0}, 0, "");
    q.try_push(c);
}

void Monkey::update_vivo(ListaObjetos& objetos, Queue<Container>& q,
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
                        AnimationType::IDLE, EntityType::MONKEY, 0, {EntityType::NONE_ENTITY, 0}, 0,
                        "");
            q.try_push(c);
        }
        contador++;
    }
}

void Monkey::throw_banana(ListaObjetos& objetos) {

    tiempo = std::chrono::system_clock::now();
    this->an_type = AnimationType::IDLE;
    throwing_banana = false;

    int aux;
    if (direccion ==
        1) {  // Si se dispara mirando a la derecha la bala sale desde la derecha del objeto
        aux = x + width;  // Si se dispara mirando a la izquierda sale a la izquierda
    } else {
        aux = x + width;
    }

    std::shared_ptr<Banana> b(new Banana(aux, y + height / 2, direccion, config));
    objetos.agregar_objeto(b);  // Se agrega al vector de colisiones
    // disminuir_municion();
}
