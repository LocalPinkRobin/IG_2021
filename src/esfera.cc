#include "objrevolucion.h"
#include "esfera.h"

Esfera::Esfera(float radio, int iteraciones, int num_vert_perfil, bool tapa_sup, bool tapa_inf) {


    float x = 0;
    float y = 0;
    float z = 0;

    float angulo = M_PI / (num_vert_perfil-1);

    //Punto superior

    Tupla3f vertice_superior = {0.0,radio, 0.0};

    for (int i = 0; i < num_vert_perfil -1; i++){
        x = vertice_superior(0) * cos(angulo * i) - vertice_superior(1) * sin(angulo * i);
        y = vertice_superior(0) * sin(angulo * i) + vertice_superior(1) * cos(angulo * i);
        z = vertice_superior(2);

		x = abs(x);
		z = abs(z);

        vectorOriginal.push_back( {x, y, z} );
    }

    vectorOriginal.push_back({0.0, -radio, 0.0});
    tapaInferior = tapa_sup;
    tapaSuperior = tapa_inf;

    
    crearMalla(vectorOriginal,iteraciones);

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

