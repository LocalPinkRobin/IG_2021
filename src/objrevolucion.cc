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
    
    tapaSuperior = tapa_sup;
    tapaInferior = tapa_inf;
    std::vector<Tupla3f> copiaVector;    
    ply::read_vertices(archivo, copiaVector);

    crearMalla(copiaVector, num_instancias,ejeRotacion);
    
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


    

}
bool ObjRevolucion::getMostrarTapas(){
    return mostrar_tapas;
}
void ObjRevolucion::dibujar_tapas (bool dibujar) {
    mostrar_tapas = dibujar;
}

void ObjRevolucion::pintar_diferido( const std::vector<Tupla3i> & caras, bool ajedrez){
    int resta = iteraciones;
    if(ajedrez){
        resta = resta/2;
    }
    int num_caras = caras.size();
    if (tapaSuperior && !mostrar_tapas){
         num_caras -= resta;
    }
    if (tapaInferior && !mostrar_tapas){
         num_caras -= resta;
    }
      glDrawElements (GL_TRIANGLES, 3*num_caras, GL_UNSIGNED_INT, 0);

}

void ObjRevolucion::pintar_inmediato( const std::vector<Tupla3i> & caras, bool ajedrez){
    int resta = iteraciones;
    if(ajedrez){
        resta = resta/2;
    }
    int num_caras = caras.size();
    if (tapaSuperior && !mostrar_tapas){
         num_caras -= resta;
    }
    if (tapaInferior && !mostrar_tapas){
         num_caras -= resta;
    }
   glDrawElements (GL_TRIANGLES, num_caras*3, GL_UNSIGNED_INT, caras.data());

}
// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un vector de puntos)

 
ObjRevolucion::ObjRevolucion(std::vector<Tupla3f> perfilOriginal, int num_instancias, bool tapa_sup, bool tapa_inf, Eje ejeRotacion) {
        
    tapaSuperior = tapa_sup;
    tapaInferior = tapa_inf;
    crearMalla(perfilOriginal, num_instancias, ejeRotacion);
    
    
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
}

void ObjRevolucion::crearMalla (const std::vector<Tupla3f> & perfil_original,
                     const int num_instancias_perf, Eje ejeRotacion){
    
    iteraciones = num_instancias_perf;
    vectorOriginal = perfil_original;
    generarVertices(num_instancias_perf, ejeRotacion);
    generarTriangulos(num_instancias_perf);
    calcular_normales();
    
}

Tupla3f ObjRevolucion::rotarVertice (Tupla3f vertice, double angulo, Eje ejeRotacion){

    Tupla3f resultado = vertice;


    if(ejeRotacion == Eje::EJEX){
                resultado[0]= vertice[0];
    //std::cout << "EJE X" << std::endl;
        resultado[1] = cos(angulo) * vertice[1] - sin(angulo) * vertice[2];
        resultado[2] = sin(angulo) * vertice[1] + cos(angulo) * vertice[2];
    } else if (ejeRotacion == Eje::EJEY){
            //std::cout << "EJE Y" << std::endl;

        resultado[0] = cos(angulo) * vertice[0] + sin(angulo) * vertice [2];
        resultado[1]= vertice[1];
        resultado[2] = -sin(angulo)* vertice[0] + cos(angulo) * vertice [2];
    } else if (ejeRotacion == Eje::EJEZ){
        resultado[0] = cos(angulo) * vertice[0] - sin(angulo) * vertice[1];
        resultado[1] = sin(angulo) * vertice[0] + cos(angulo) * vertice[1];
    }
    /*
    std::cout << "VERTICES ORIGINALES" << std::endl;
    std::cout << vertice[0] << "       " << vertice[1] << "        " << vertice[2] << std::endl;
    std::cout << "VERTICES ROTADOS" << std::endl;
    std::cout << resultado[0] << "       " << resultado[1] << "        " << resultado[2] << std::endl;
    */
    return (resultado);

}

void ObjRevolucion::ordenaVerticesDecreciente(Eje ejeRotacion){
    bool estaOrdenado = false;
    
    if(ejeRotacion == Eje::EJEX){
        estaOrdenado = vectorOriginal[0][0] < vectorOriginal[vectorOriginal.size()-1][0];
    } else if(ejeRotacion == Eje::EJEY){
        estaOrdenado = vectorOriginal[0][1] < vectorOriginal[vectorOriginal.size()-1][1];
    } else if(ejeRotacion == Eje::EJEZ){
        estaOrdenado = vectorOriginal[0][2] < vectorOriginal[vectorOriginal.size()-1][2];
    }

    if (!estaOrdenado){
        vectorOriginal = std::vector<Tupla3f>(vectorOriginal.rbegin(), vectorOriginal.rend());
    }
}


void ObjRevolucion::generarVertices( int iteraciones, Eje ejeRotacion){
    
    //¿Tenemos el vector ordenado?
    ordenaVerticesDecreciente(ejeRotacion);
    
    //Cargamos el PLY de un perfil
    
    //Nos guardamos los vertices polo norte y polo sur
    //Los eliminamos del vector original

    if(ejeRotacion == Eje::EJEX){
        //Comprobamos tapa superior
        if(comparaFloats(vectorOriginal[vectorOriginal.size()-1][1],0) && comparaFloats(vectorOriginal[vectorOriginal.size()-1][2],0)){
            v_superior = vectorOriginal[vectorOriginal.size()-1];
            vectorOriginal.pop_back();
        } else {
            v_superior = {vectorOriginal[vectorOriginal.size()-1][0], 0, 0};
        }

        //Comprobamos tapa inferior
        if(comparaFloats(vectorOriginal[0][1],0) && comparaFloats(vectorOriginal[0][2],0)){
            v_inferior = vectorOriginal[0];
            vectorOriginal.erase(vectorOriginal.begin());
        } else {
            v_inferior = {vectorOriginal[0][0], 0, 0};
        }


    } else if (ejeRotacion == Eje::EJEY){
        if(comparaFloats(vectorOriginal[vectorOriginal.size()-1][0],0) && comparaFloats(vectorOriginal[vectorOriginal.size()-1][2],0)){
            v_superior = vectorOriginal[vectorOriginal.size()-1];
            vectorOriginal.pop_back();
        } else {
            v_superior = {0,vectorOriginal[vectorOriginal.size()-1][1], 0};
        }

        if(comparaFloats(vectorOriginal[0][0],0) && comparaFloats(vectorOriginal[0][2],0)){
            v_inferior = vectorOriginal[0];
            vectorOriginal.erase(vectorOriginal.begin());
        } else {
            v_inferior = {0,vectorOriginal[0][1], 0};
        }
    
    } else if (ejeRotacion == Eje::EJEZ){
        if(comparaFloats(vectorOriginal[vectorOriginal.size()-1][0],0) && comparaFloats(vectorOriginal[vectorOriginal.size()-1][1],0)){
            v_superior = vectorOriginal[vectorOriginal.size()-1];
            vectorOriginal.pop_back();
        } else {
            v_superior = {0, 0, vectorOriginal[vectorOriginal.size()-1][2]};
        }

        if(comparaFloats(vectorOriginal[0][0],0) && comparaFloats(vectorOriginal[0][1],0)){
            v_inferior = vectorOriginal[0];
            vectorOriginal.erase(vectorOriginal.begin());
        } else {
            v_inferior = {0, 0, vectorOriginal[0][2]};
        }
       
    }
    //Generamos y rotamos
    Tupla3f generado;
    for (int i = 0; i < iteraciones; i++){
        for (int j = 0; j < vectorOriginal.size(); j++){
            generado = rotarVertice(vectorOriginal[j], (2.0*M_PI*i)/iteraciones,ejeRotacion);
            v.push_back(generado);
        }
    }

    //Ponemos los polos
    

 

}
void ObjRevolucion::generarTriangulos(int iteraciones){
    for (int i = 0; i < iteraciones; i++){
        for (int j = 0; j < vectorOriginal.size()-1; j++){
            int a = vectorOriginal.size()*i + j;
            int b = vectorOriginal.size()*((i+1)%iteraciones) +j;
            f.push_back({a, b, b+1});
            f.push_back({a, b+1, a+1});
        }
    }

    if(tapaInferior){
        v.push_back(v_inferior);
        for(int i = 0; i < iteraciones; i++){
            f.push_back({i*vectorOriginal.size(),v.size()-1, ((i+1) % iteraciones )*vectorOriginal.size() });
        }
    }

    if (tapaSuperior){
        v.push_back(v_superior);

        for(int i = 0; i < iteraciones; i++){
            f.push_back({((i+1) % iteraciones )*vectorOriginal.size() + vectorOriginal.size()-1, v.size()-1, i*vectorOriginal.size() + vectorOriginal.size()-1});
        }
    }
}
