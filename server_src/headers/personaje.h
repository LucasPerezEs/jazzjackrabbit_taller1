#ifndef PERSONAJE_H_
#define PERSONAJE_H_

#include <vector>

#include "../../common_src/headers/queue.h"

#include "contenedor.h"
#include "mapa.h"
#include "objeto.h"


class ListaObjetos;

class Bala: public Objeto {
protected:
    int vel;

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
    int municion;
    virtual void disminuir_municion();

public:
    Arma();
    void disparar(ListaObjetos& objetos, float x, float w, float y, float h, int d);
};

class Personaje: public Ente {
protected:
    bool movingright;
    bool movingleft;
    bool jumping;
    float velx;
    float vely;
    Arma arma;

public:
    int municion;
    bool disparando;
    Personaje(float x, float y, float w, float h, int vida);
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
    virtual void update(Mapa& m, ListaObjetos& objetos, Queue<Contenedor>& q) override;
};

#endif
