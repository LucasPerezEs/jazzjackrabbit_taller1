#ifndef OBJETO_H_
#define OBJETO_H_

#include <vector>
#include <map>

class Enemigo;
class Personaje;
class Bala;

class Objeto {
    public:
    int x; 
    int y;
    int width;
    int height;
    bool borrar;

    public:
    Objeto(int x, int y, int w, int h);

    virtual void avanzar();

    virtual void colision(Objeto &o) = 0;
    virtual void colision(Personaje &o);
    virtual void colision(Enemigo &o);
    virtual void colision(Bala &o);
};

class Ente: public Objeto {
    protected:
    int direccion;
    public:
    int vida;

    Ente(int x, int y, int w, int h, int vida);
    void RecibirDaño(int d);
    bool vivo();
    virtual void mover(int movx, int movy) = 0;
};

class Bala: public Objeto {
    protected:
    int vel;
    public:
    int daño;
    Bala(int x, int y, int d);
    virtual void colision(Objeto &o);
    virtual void avanzar();
};

class Arma {
    public:
    void disparar(std::map<Objeto*, Objeto*>& objetos, int x, int w, int y, int h, int d);
};

#endif