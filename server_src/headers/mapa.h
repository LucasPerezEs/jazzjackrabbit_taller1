#ifndef MAPA_H_
#define MAPA_H_

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
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
private:
    std::vector<std::vector<int>> spawns;
    std::vector<std::vector<int>> spawnsPersonaje;

public:
    std::vector<std::vector<int>> spawnsOtros;
    std::vector<Piso*> objetos;
    std::vector<DiagonalIzquierda*> diagonalesIzq;
    std::vector<DiagonalDerecha*> diagonalesDer;
    std::vector<std::vector<int>> cargarCSV(const std::string& ruta);
    explicit Mapa(const std::string& mapName);
    bool CheckColision(float x, float y, float w, float h);
    std::vector<int> get_spawn(int type);
    void spawn(ListaObjetos& objetos, std::vector<std::shared_ptr<Ente>>& entes, std::map<std::string, float> &config, Queue<Container>& q);

    ~Mapa();
};

#endif
