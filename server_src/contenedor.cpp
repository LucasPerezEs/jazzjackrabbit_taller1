#include "headers/contenedor.h"

Contenedor::Contenedor(int msg_code, int id, float x, float y, float w, float h, bool borrar) {
    vector.push_back(msg_code);
    vector.push_back(id);
    vector.push_back(x);
    vector.push_back(y);
    vector.push_back(w);
    vector.push_back(h);
    vector.push_back(borrar);
}

int Contenedor::msg_code() { return vector[0]; }

int Contenedor::id() { return vector[1]; }

float Contenedor::posx() { return vector[2]; }

float Contenedor::posy() { return vector[3]; }

float Contenedor::width() { return vector[4]; }

float Contenedor::height() { return vector[5]; }

bool Contenedor::borrar() { return vector[6]; }
