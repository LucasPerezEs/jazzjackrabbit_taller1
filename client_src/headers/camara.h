#ifndef CAMARA_H_
#define CAMARA_H_

class Camara {
    public:
    float escalax;
    float escalay;
    float x;
    float y;

    private:
    float width;
    float height;
    float limitex;
    float limitey;

    public:
    Camara(float x, float y, float width, float height, float limitex, float limitey);
    bool en_rango(float x, float y, float width, float height);
    void actualizar_pos(float x, float y);
    float escalaX();
    float escalaY();
    void zoomIn();
    void zoomOut();
    
};

#endif