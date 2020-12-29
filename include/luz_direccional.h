#ifndef LUZ_DIRECCIONAL_H_INCLUDED
#define LUZ_DIRECCIONAL_H_INCLUDED

#include "luz.h"
#include "aux.h"


class LuzDireccional : public Luz {

    protected:
        float alpha;
        float beta;
        Tupla4f posicion_original;
        void recalcularPosicion();

    public:
    
    LuzDireccional (Tupla3f direccion, GLenum idLuzOpenGL, Tupla4f colorAmbiente,
                    Tupla4f colorEspecular, Tupla4f colorDifuso);
    void variarAnguloAlpha (float incremento);
    void variarAnguloBeta (float incremento);

} ;




#endif