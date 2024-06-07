#ifndef PERSONAJE_H_
#define PERSONAJE_H_

#include <chrono>
#include <vector>

#include "../../common_src/headers/queue.h"

#include "contenedor.h"
#include "mapa.h"
#include "objeto.h"


class ListaObjetos;

class Bala: public Objeto {
protected:
    float vel;

public:
    int danio;
    Bala(float x, float y, int d);
    virtual void colision(Objeto& o) override;
    virtual void colision(Enemigo& o) override;
    virtual void update(Mapa& m, ListaObjetos& objetos, Queue<Contenedor>& q) override;
    virtual void eliminar() override;
};

class Arma {  // No se si es necesaria esta clase
protected:
    int espera;
    std::chrono::system_clock::time_point tiempo;
    int municion;
    virtual void disminuir_municion();

public:
    Arma();
    void disparar(ListaObjetos& objetos, float x, float w, float y, float h, int d);
};

class Personaje: public Ente {
protected:
    int score;
    int espera_idle;
    int espera_shoot;
    std::chrono::system_clock::time_point tiempo;
    bool movingright;
    bool movingleft;
    bool jumping;
    float velx;
    float vely;
    Arma arma;

public:
    int municion;
    bool disparando;
    Personaje(float x, float y, float w, float h, int vida, EntityType en_type,
              AnimationType an_type);
    virtual void colision(Objeto& o) override;
    virtual void colision(Enemigo& e) override;
    virtual void colision(Municion& m) override;
    void disparar(ListaObjetos& objetos);
    void moveRigth();
    void moveLeft();
    void stopMovingRight();
    void stopMovingLeft();
    void run();
    void stoprunning();
    void jump();
    void set_id(int i);
    void add_score(int score);
    virtual void update(Mapa& m, ListaObjetos& objetos, Queue<Contenedor>& q) override;
    virtual void update_vivo(ListaObjetos& objetos, Queue<Contenedor>& q) override;
};

#endif
