#include "objrevolucion.h"
#include "cilindro.h"

Cilindro::Cilindro(float altura, float radio, int iteraciones, bool tapa_sup, bool tapa_inf, Eje ejeRotacion) {

    tapaSuperior = tapa_sup;
    tapaInferior = tapa_inf;

    vectorOriginal.resize(2);

    if (ejeRotacion == Eje::EJEY){
        vectorOriginal[0] = {radio, -altura/2.0, 0.0};
        vectorOriginal[1] = {radio, altura/2.0, 0.0};
    } else if(ejeRotacion == Eje::EJEX){
        vectorOriginal[0] = {-altura/2.0, radio, 0.0};
        vectorOriginal[1] = {altura/2.0,radio, 0.0};
    } else if (ejeRotacion == Eje::EJEZ){
        vectorOriginal[0] = {0.0, radio, -altura/2.0};
        vectorOriginal[1] = {0.0,radio, altura/2.0};        
    }
    
    crearMalla(vectorOriginal,iteraciones,ejeRotacion);

};

