#ifndef ENEMIGO_H_
#define ENEMIGO_H_

#include <map>
#include <string>
#include <unordered_map>

#include "../../common_src/headers/queue.h"

#include "gold_coin.h"
#include "lista_objetos.h"
#include "municion.h"
#include "objeto.h"
#include "personaje.h"
#include "rocket_pickup.h"
#include "zanahoria.h"


class Projectile;
class ListaObjetos;

class Enemigo: public Ente {
protected:
    float max_life;
    int damage;
    float speed;
    float prob_carrot;
    float prob_ammo;
    float prob_goldcoin;
    float prob_rocket;
    std::map<std::string, float>& config;

public:
    Enemigo(float x, float y, float w, float h, float max_life, float speed, float damage,
            float prob_carrot, float prob_ammo, float prob_goldcoin, float prob_rocket,
            EntityType en_type, AnimationType an_type, std::map<std::string, float>& config);
    virtual void colision(Objeto& o) override;
    virtual void colision(Personaje& p) override;
    virtual void colision(Projectile& b) override;
    virtual void update(Mapa& m, ListaObjetos& objetos, Queue<Container>& q) override = 0;
    virtual void update_vivo(
            ListaObjetos& objetos, Queue<Container>& q,
            std::map<uint32_t, std::shared_ptr<Personaje>>& clientCharacters, std::shared_ptr<Ente> e) override = 0;
    virtual void drop_item(ListaObjetos& objetos, Queue<Container>& q);
    int get_damage();
};


#endif
