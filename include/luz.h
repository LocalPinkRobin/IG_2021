#ifndef LUZ_H_INCLUDED
#define LUZ_H_INCLUDED

#include "aux.h"


class Luz {

    protected:

    Tupla4f posicion;

    Tupla4f colorAmbiente;
    Tupla4f colorDifuso;
    Tupla4f colorEspecular;

    GLenum id;

    public:

    Luz();
    void activar();


};

#endif