#ifndef MAPA_H_
#define MAPA_H_

#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
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

class DiagonalIzquierda {
public:
    float x;
    float y;
    float w;
    float h;
    DiagonalIzquierda(float x, float y, float w, float h);
    bool colision(float x, float y, float w, float h);
};

class DiagonalDerecha {
    public:
    float x;
    float y;
    float w;
    float h;
    DiagonalDerecha(float x, float y, float w, float h);
    bool colision(float x, float y, float w, float h);
};

class Mapa {
public:
    std::vector<Piso*> objetos;
    std::vector<DiagonalIzquierda*> diagonalesIzq;
    std::vector<DiagonalDerecha*> diagonalesDer;
    std::vector<std::vector<int>> cargarCSV(const std::string& ruta);
    Mapa();
    bool CheckColision(float x, float y, float w, float h);
    ~Mapa();
};

#endif
