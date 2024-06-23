#ifndef PERSONAJE_H_
#define PERSONAJE_H_

#include <chrono>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

#include "../../common_src/headers/Container.h"
#include "../../common_src/headers/queue.h"
#include "../../common_src/headers/sound_commands.h"

#include "banana.h"
#include "enemigo.h"
#include "lista_objetos.h"
#include "mapa.h"
#include "municion.h"
#include "objeto.h"
#include "zanahoria_envenenada.h"

class ListaObjetos;
class Projectile;
class Bullet;
class Rocket;

class Arma {  // No se si es necesaria esta clase
protected:
    std::map<std::string, float>& config;
    std::chrono::system_clock::time_point tiempo;
    std::vector<EntityType> ammo_types;
    std::map<EntityType, int> ammo_inventory;
    std::map<EntityType, int> fire_rates;
    int current_ammo;

    void init_ammo();
    void spawn_projectile(ListaObjetos& objetos, EntityType ammo, int x, int y, int d,
                          int shooter_id, std::map<std::string, float>& config);

public:
    explicit Arma(std::map<std::string, float>& config);
    bool disparar(ListaObjetos& objetos, int shooter_id, float x, float w, float y, float h, int d,
                  Queue<Container>& q);
    bool change_selected_ammo();
    int remaining_ammo();
    void add_ammo(EntityType ammo, int n);
};

enum PlayerState { INTOXICATED = 0x30, HURTED = 0x31, NORMAL = 0x32 };

class Personaje: public Ente {
protected:
    int espera_idle;
    int espera_shoot;
    int espera_hurt;
    std::chrono::system_clock::time_point tiempo;
    std::chrono::system_clock::time_point last_hurt;
    std::chrono::system_clock::time_point intoxicated_start;
    bool movingright;
    bool movingleft;
    bool jumping;
    float velx;
    float vely;
    bool special_action_active;
    float direccion_movimientox;
    float direccion_movimientoy;
    float jump_speed;
    int killed_by_id;
    std::map<std::string, float>& config;
    Arma arma;
    PlayerState state;
    Queue<Container>& q;

    void check_idle();
    virtual void update_position();
    void check_colisions(Mapa& m, float aux_x, float aux_y);
    virtual void check_special_action(bool col_x, bool col_y) = 0;

public:
    std::string name;
    int score;
    int danio_ataque_especial;
    int municion;
    bool disparando;
    Personaje(float x, float y, float w, float h, EntityType en_type, AnimationType an_type,
              std::map<std::string, float>& config, Queue<Container>& q, std::string name);

    virtual void colision(ZanahoriaEnvenenada& ze) override;
    virtual void colision(Objeto& o) override;
    virtual void colision(Enemigo& e) override;
    virtual void colision(Municion& m) override;
    virtual void colision(
            Banana& b) override;  // Banana y Bala deberian pertenecer a una clase 'Proyectil'
    virtual void colision(Projectile& b) override;
    virtual void colision(Personaje& p) override;

    void disparar(ListaObjetos& objetos);
    void moveRigth();
    void moveLeft();
    void stopMovingRight();
    void stopMovingLeft();
    void run();
    void stoprunning();
    void jump();
    virtual void special_action() = 0;
    void set_id(uint32_t i);
    void add_score(int score);
    void add_ammo(EntityType ammo, int n);
    void check_dead(int killer_id);
    bool has_special_action_active();
    void change_selected_ammo();
    virtual void update(Mapa& m, ListaObjetos& objetos, Queue<Container>& q) override;
    virtual void update_vivo(ListaObjetos& objetos, Queue<Container>& q,
                             std::unordered_map<uint32_t, Personaje*>& clientCharacters) override;
};

#endif
