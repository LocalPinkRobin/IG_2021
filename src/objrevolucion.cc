#include "aux.h"
#include "objrevolucion.h"
#include <cmath>




// *****************************************************************************
//
// Clase ObjRevolucion (práctica 2)
//
// *****************************************************************************


// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un PLY)

ObjRevolucion::ObjRevolucion() {}

ObjRevolucion::ObjRevolucion(const std::string & archivo, int num_instancias, bool tapa_sup, bool tapa_inf, Eje ejeRotacion) {

    

}

// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un vector de puntos)

 
ObjRevolucion::ObjRevolucion(std::vector<Tupla3f> archivo, int num_instancias, bool tapa_sup, bool tapa_inf, Eje ejeRotacion) {
    
}

void ObjRevolucion::crearMalla(std::vector<Tupla3f> perfil_original, int num_instancias) {
}

Tupla3f ObjRevolucion::rotarVertice (Tupla3f vertice, double angulo, Eje ejeRotacion){

    Tupla3f resultado = vertice;

    if(ejeRotacion == Eje::EJEX){
        resultado[1] = cos(angulo) * resultado[1] - sin(angulo) * resultado[2];
        resultado[2] = cos(angulo) * resultado[1] + sin(angulo) * resultado[2];
    } else if (ejeRotacion == Eje::EJEY){
        resultado[0] = cos(angulo) * resultado[0] + sin(angulo) * resultado [2];
        resultado[2] = -sin(angulo)* resultado[0] + cos(angulo) * resultado [2];
    } else if (ejeRotacion == Eje::EJEZ){
        resultado[0] = cos(angulo) * resultado[0] - sin(angulo) * resultado[1];
        resultado[2] = cos(angulo) * resultado[0] + sin(angulo) * resultado[1];
    }

    return (resultado);

}

void ObjRevolucion::ordenaVerticesDecreciente(Eje ejeRotacion){
    bool estaOrdenado = false;
    
    if(ejeRotacion == Eje::EJEX){
        estaOrdenado = v[0][0] < v[v.size()-1][0];
    } else if(ejeRotacion == Eje::EJEY){
        estaOrdenado = v[0][1] < v[v.size()-1][1];
    } else if(ejeRotacion == Eje::EJEZ){
        estaOrdenado = v[0][2] < v[v.size()-1][2];
    }

    if (!estaOrdenado){
        v = std::vector<Tupla3f>(v.rbegin(), v.rend());
    }
}


void ObjRevolucion::generarVertices(const std::string & archivo, int iteraciones, Eje ejeRotacion){
    
    ply::read_vertices(archivo, v);

    //¿Tenemos el vector ordenado?
    ordenaVerticesDecreciente(ejeRotacion);
    
    //Cargamos el PLY de un perfil
    Tupla3f v_superior, v_inferior;
    
    //Nos guardamos los vertices polo norte y polo sur
    //Los eliminamos del vector original

    if(ejeRotacion == Eje::EJEX){
        //Comprobamos tapa superior
        if(comparaFloats(v[v.size()-1][1],0) && comparaFloats(v[v.size()-1][2],0)){
            v_superior = v[v.size()-1];
            v.pop_back();
        } else {
            v_superior = {v[v.size()-1][0], 0, 0};
        }

        //Comprobamos tapa inferior
        if(comparaFloats(v[0][1],0) && comparaFloats(v[0][2],0)){
            v_inferior = v[0];
            v.pop_back();
        } else {
            v_inferior = {v[0][0], 0, 0};
        }


    } else if (ejeRotacion == Eje::EJEY){
        if(comparaFloats(v[v.size()-1][0],0) && comparaFloats(v[v.size()-1][2],0)){
            v_superior = v[v.size()-1];
            v.pop_back();
        } else {
            v_superior = {0,v[v.size()-1][1], 0};
        }

        if(comparaFloats(v[0][0],0) && comparaFloats(v[0][2],0)){
            v_inferior = v[0];
            v.pop_back();
        } else {
            v_inferior = {0,v[0][1], 0};
        }
    
    } else if (ejeRotacion == Eje::EJEZ){
        if(comparaFloats(v[v.size()-1][0],0) && comparaFloats(v[v.size()-1][1],0)){
            v_superior = v[v.size()-1];
            v.pop_back();
        } else {
            v_superior = {0, 0, v[v.size()-1][2]};
        }

        if(comparaFloats(v[0][0],0) && comparaFloats(v[0][1],0)){
            v_inferior = v[0];
            v.pop_back();
        } else {
            v_inferior = {0, 0, v[0][2]};
        }
       
    }
    
    v_inferior = v[0];

    v.erase(v.begin());

    //Generamos y rotamos
    Tupla3f generado;
    for (int i = 0; i < iteraciones; i++){
        for (int j = 0; j < v.size(); j++){
            generado = rotarVertice(v[j], (2*M_PI*i)/iteraciones,ejeRotacion);
            v.push_back(generado);
        }
    }

    //Ponemos los polos
    v.push_back(v_superior);
    v.push_back(v_inferior);

}