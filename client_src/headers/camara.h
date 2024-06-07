#ifndef CAMARA_H_
#define CAMARA_H_

class Camara {
    public:
    int escalax;
    int escalay;
    float x;
    float y;

    private:
    int width;
    int height;
    bool first;
    int limitex;
    int limitey;

    public:
    Camara(float x, float y, int width, int height, int limitex, int limitey);
    bool en_rango(float x, float y, float width, float height);
    void actualizar_pos(float x, float y);
    int escalaX();
    int escalaY();
    
};

#endif