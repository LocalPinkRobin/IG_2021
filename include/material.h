#ifndef MATERIAL_H_INCLUDED
#define MATERIAL_H_INCLUDED
#include "aux.h"


class Material {
    private:
    Tupla4f ambiente;
    Tupla4f especular;
    Tupla4f difuso;
    float brillo;

    public:
    Material();
    Material (Tupla4f ambiente, Tupla4f difuso, Tupla4f especular, float brillo);
    
    void aplicar();
    void operator = (const Material & otro);
    
} ;




#endif