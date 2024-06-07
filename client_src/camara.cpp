#include "headers/camara.h"

Camara::Camara(float x, float y, int width, int height, int limitex, int limitey):
    escalax(32), escalay(24),  x(x), y(y), width(width), height(height), first(true), limitex(limitex), limitey(limitey)
    {}

bool Camara::en_rango(float x, float y, float width, float height) {
    float width_escalado = this->width/escalax;
    float height_escalado = this->height/escalay;
    if ((x + width) > (this->x) && (this->x + width_escalado) > x && (y + height) > (this->y - height_escalado) && (this->y) > y) {
        return true;
    }
    return false;
}

void Camara::actualizar_pos(float x, float y) {
    if (first) {
        this->x = x - this->width/(2*escalax);
        this->y = y + (this->height/escalay) - 2;
        first = false;
    }
    else {
        if (x - this->width/(2*escalax) < 0)
            this->x = 0;
        else if (x + this->width/(2*escalax) > limitex-1) {
            this->x = limitex - this->width/(escalax);
        }
        else {
            this->x = x - this->width/(2*escalax);
        }

        if (this->y - y <  (this->height/(2*escalay)))
            this->y = y + this->height/(2*escalay);
        if (this->y - y > this->height/(escalay) - 2)
            this->y = y + this->height/(escalay) - 2;
    }
    
}

int Camara::escalaX() {
    return escalax;
}

int Camara::escalaY() {
    return escalay;
}
