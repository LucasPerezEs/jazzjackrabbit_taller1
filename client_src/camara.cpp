#include "headers/camara.h"
#include <cmath>
#include <iostream>

Camara::Camara(float x, float y, float width, float height, float limitex, float limitey):
    escalax(32), escalay(24),  x(x), y(y), width(width), height(height), first(true), limitex(limitex), limitey(limitey)
    {}

bool Camara::en_rango(float x, float y, float width, float height) {
    float width_escalado = std::floor(this->width/escalax);
    float height_escalado = std::floor(this->height/escalay);
    if ((x + width) > (this->x) && (this->x + width_escalado) > x && (y + height) > (this->y - height_escalado) && (this->y) > y) {
        return true;
    }
    return false;
}

void Camara::actualizar_pos(float x, float y) {
    std::cout << "pos y: " << y << "\n";
    std::cout << "pos y camara: " << this->y << "\n";
    std::cout << "bloques que entran en pantalla: " << std::ceil((this->height/escalay)) << "\n";
    std::cout << "escala y: " << escalay << "\n";
    if (first) {
        this->x = x - (this->width/(2*escalax));
        this->y = y + std::ceil((this->height/escalay)) - 2;
        first = false;
    }
    else {

        this->x = x - (this->width/(2*escalax));

        if (this->x < 0)
            this->x = 0;
        if (this->x + this->width/(escalax) > limitex) {
            this->x = limitex - (this->width/(escalax));
        }

        if (this->y - y < (this->height/(2*escalay)))
            this->y += (this->height/(2*escalay)) - (this->y - y);
        else if (this->y - y > this->height/(escalay) - 2)
            this->y += -(this->y - y) + (this->height/(escalay) - 2);
        
        if (this->y > limitey)
            this->y = limitey;
        if (this->y - this->height/(escalay) < 0)
            this->y = this->height/(escalay);
    }
    
}

float Camara::escalaX() {
    return escalax;
}

float Camara::escalaY() {
    return escalay;
}

void Camara::zoomIn() {
    if (escalax < 80 && escalay < 60) {
        escalax += 4;
        escalay += 3;
        //first = true;
    }
}

void Camara::zoomOut() {
    if (escalax > 4 && escalay*limitey > 600) {
        escalax -= 4;
        escalay -= 3;
        //first = true;
    }
}