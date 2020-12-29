
#include "luz_posicional.h"
#include "aux.h"


LuzPosicional::LuzPosicional (Tupla3f posicion, GLenum idLuzOpenGL, Tupla4f colorAmbiente,
                        Tupla4f colorEspecular, Tupla4f colorDifuso) {

    this->posicion = {posicion[0], posicion[1], posicion[2], 1};
    this->colorAmbiente = colorAmbiente;
    this->colorDifuso = colorDifuso;
    this->colorEspecular = colorEspecular;
    this->id = idLuzOpenGL; 

}

