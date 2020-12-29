#ifndef LUZ_POSICIONAL_H_INCLUDED
#define LUZ_POSICIONAL_H_INCLUDED

#include "luz.h"
#include "aux.h"


class LuzPosicional : public Luz {

    public:
    
    LuzPosicional (Tupla3f posicion, GLenum idLuzOpenGL, Tupla4f colorAmbiente,
                        Tupla4f colorEspecular, Tupla4f colorDifuso);

} ;


#endif