#include "objrevolucion.h"
#include "cono.h"

Cono::Cono(float altura, float radio, int iteraciones, Eje ejeRotacion) {

    tapaInferior = true;
    tapaSuperior = true;

    vectorOriginal.resize(2);

    if (ejeRotacion == Eje::EJEY){
        std::cout << "Cono EjeY" << std::endl;
        
        vectorOriginal[0] = {0.0, altura, 0.0};
        vectorOriginal[1] = {radio, 0.0, 0.0};
    
    } else if(ejeRotacion == Eje::EJEX){
                std::cout << "Cono EjeX" << std::endl;

        vectorOriginal[0] = {altura, 0.0, 0.0};
        vectorOriginal[1] = {0.0,radio, 0.0};

    } else if (ejeRotacion == Eje::EJEZ){
                std::cout << "Cono EjeZ" << std::endl;

        vectorOriginal[0] = {0.0, 0.0, altura};
        vectorOriginal[1] = {0.0,radio, 0.0};        
    }
    
    crearMalla(vectorOriginal,iteraciones,ejeRotacion);

};

