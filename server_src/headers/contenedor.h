#ifndef CONTENEDOR_H_
#define CONTENEDOR_H_

#include <vector>

class Contenedor {
private:
    std::vector<float> vector;

public:
    Contenedor(float id, float x, float y, float w, float h, float borrar);
    float id();
    float posx();
    float posy();
    float width();
    float height();
    float borrar();
};
#endif
