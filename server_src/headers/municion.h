#include "objeto.h"

class Municion: public Objeto {
public:
    Municion(float x, float y);

    virtual void colision(Objeto& o) override;
    virtual void colision(Personaje& p) override;
    virtual void eliminar() override;
};
