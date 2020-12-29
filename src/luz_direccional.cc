#include "luz_direccional.h"
#include "aux.h"


LuzDireccional::LuzDireccional (Tupla3f direccion, GLenum idLuzOpenGL, Tupla4f colorAmbiente,
                    Tupla4f colorEspecular, Tupla4f colorDifuso){

    this->posicion = {direccion[0], direccion[1], direccion[2], 0};
    this->colorAmbiente = colorAmbiente;
    this->colorDifuso = colorDifuso;
    this->colorEspecular = colorEspecular;
    this->id = idLuzOpenGL; 
    posicion_original = posicion;


   alpha = abs(atan2f( direccion(0), direccion(2) ));

   beta = asin( direccion(1)/ sqrt(direccion.lengthSq()) );

    if (direccion(0) < 0){
      alpha += M_PI ;
    }

}

void LuzDireccional::recalcularPosicion(){
    posicion(0) = sin(alpha) * cos(beta) * sqrt(posicion_original.lengthSq());
    posicion(1) = sin(beta) * sqrt(posicion_original.lengthSq());
    posicion(2) = cos(alpha) * cos(beta) * sqrt(posicion_original.lengthSq());
}

void LuzDireccional::variarAnguloAlpha(float incremento) {
    alpha += incremento;
    alpha = fmod(alpha,M_PI*2);

    recalcularPosicion();

}

void LuzDireccional::variarAnguloBeta(float incremento){
    beta += incremento;

    if (beta < -(M_PI/2)) {
        beta = -(M_PI/2);
    } else if (beta > M_PI/2) {
        beta = M_PI/2;
    }

}
