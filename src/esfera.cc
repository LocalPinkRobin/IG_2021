#include "objrevolucion.h"
#include "esfera.h"

Esfera::Esfera(float radio, int iteraciones, int num_vert_perfil) {


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
    tapaInferior = false;
    tapaSuperior = false;

    
    crearMalla(vectorOriginal,iteraciones);

};

