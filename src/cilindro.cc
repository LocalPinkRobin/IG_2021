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
    c.resize(v.size());  //Los colores cambian cada vez que dibujamos por si cambiamos la forma de visualizacion
    c_aj1.resize(v.size());
    c_aj2.resize(v.size());
    
    color = {69/255.0, 245/255.0, 186/255.0};
    color_aj_1 = {1.0, 0.6, 0.8};
    color_aj_2 = {0.0, 0.0, 0.0};
    color_aristas = {1,0,0};
    color_vertices = {0,0,1};

    
    colorear(0);
    colorear(3);
};

