#ifndef MAPA_H_
#define MAPA_H_

#include <vector>

#include "objeto.h"

class Piso {
public:
    float x;
    float y;
    float w;
    float h;
    Piso(float x, float y, float w, float h);
    bool colision(float x, float y, float w, float h);
};

class Diagonal {
public:
    float x;
    float y;
    float w;
    float h;
    Diagonal();
};

class Mapa {
public:
    std::vector<Piso*> objetos;
    Mapa();
    bool CheckColision(float x, float y, float w, float h);
    ~Mapa();
};

#endif
