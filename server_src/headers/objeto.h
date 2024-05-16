#ifndef OBJETO_H_
#define OBJETO_H_

#include <map>
#include <vector>

class Enemigo;
class Personaje;
class Bala;
class Mapa;

class Objeto {
public:
    float x;  // estos atributos es la hitbox del objeto
    float y;
    float width;
    float height;
    bool borrar;  // borrar se usa para borrar del map de colisiones al objeto

public:
    Objeto(float x, float y, float w, float h);

    virtual void update(Mapa& m);

    virtual void colision(Objeto& o) = 0;
    virtual void colision(Personaje& o);
    virtual void colision(Enemigo& o);
    virtual void colision(Bala& o);
};

class Ente: public Objeto {  // objetos con vida
protected:
    int direccion;  // para donde se mueven
public:
    int vida;

    Ente(float x, float y, float w, float h, int vida);
    void RecibirDanio(int d);
    bool vivo();
};

class Bala: public Objeto {
protected:
    int vel;

public:
    int danio;
    Bala(float x, float y, int d);
    virtual void colision(Objeto& o) override;
    virtual void update(Mapa& m) override;
};

class Arma {  // No se si es necesaria esta clase
public:
    void disparar(std::map<Objeto*, Objeto*>& objetos, float x, float w, float y, float h, int d);
};

#endif
