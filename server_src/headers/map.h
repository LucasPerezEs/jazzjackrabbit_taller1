#ifndef MAPA_H_
#define MAPA_H_

#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "object.h"

class Floor {
public:
    float x;
    float y;
    float w;
    float h;
    Floor(float x, float y, float w, float h);
    bool colision(float x, float y, float w, float h);
};

class LeftDiagonal {
public:
    float x;
    float y;
    float w;
    float h;
    LeftDiagonal(float x, float y, float w, float h);
    bool colision(float x, float y, float w, float h);
};

class RightDiagonal {
public:
    float x;
    float y;
    float w;
    float h;
    RightDiagonal(float x, float y, float w, float h);
    bool colision(float x, float y, float w, float h);
};

class Map {
private:
    std::vector<std::vector<int>> spawns;
    std::vector<std::vector<int>> spawnsPersonaje;

public:
    std::vector<std::vector<int>> spawnsOtros;
    std::vector<Floor*> objetos;
    std::vector<LeftDiagonal*> diagonalesIzq;
    std::vector<RightDiagonal*> diagonalesDer;
    std::vector<std::vector<int>> cargarCSV(const std::string& ruta);
    explicit Map(const std::string& mapName);
    bool CheckColision(float x, float y, float w, float h);
    std::vector<int> get_spawn(int type);
    void spawn(ObjectList& objetos, std::vector<std::shared_ptr<Entity>>& entes,
               std::map<std::string, float>& config, Queue<Container>& q);

    ~Map();
};

#endif
