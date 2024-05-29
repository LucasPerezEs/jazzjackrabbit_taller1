#ifndef CONTENEDOR_H_
#define CONTENEDOR_H_

#include <vector>

class Contenedor {
private:
    std::vector<float> vector;

public:
    Contenedor(int msg_code, int id, float x, float y, float w, float h, bool borrar);
    int msg_code();
    int id();
    float posx();
    float posy();
    float width();
    float height();
    bool borrar();
};
#endif
