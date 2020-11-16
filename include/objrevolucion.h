// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Cubo.h

//
// #############################################################################

#ifndef OBJREVOLUCION_H_INCLUDED
#define OBJREVOLUCION_H_INCLUDED

#include "aux.h"
#include "malla.h"
#include "ply_reader.h"

// *****************************************************************************
//
// clases derivadas de Malla3D (definen constructores específicos)
//
// *****************************************************************************

// *****************************************************************************
// Cubo con centro en el origen y lado unidad por defecto
// (tiene 9 vertices y 6 caras)
enum class Eje {
    EJEX, EJEY,EJEZ
};


class ObjRevolucion : public Malla3D {
public:
   ObjRevolucion();
   ObjRevolucion(const std::string & archivo, int num_instancias, bool tapa_sup=true, bool tapa_inf=true, Eje ejeRotacion= Eje::EJEY) ;
   ObjRevolucion(std::vector<Tupla3f> archivo, int num_instancias, bool tapa_sup=true, bool tapa_inf=true, Eje ejeRotacion = Eje::EJEY) ;

   bool tapas ();

private:
    void crearMalla(std::vector<Tupla3f> perfil_original, int num_instancias);
    void generarVertices(const std::string & archivo, int iteraciones,Eje ejeRotacion);
    Tupla3f rotarVertice (Tupla3f vertice, double angulo, Eje ejeRotacion);

    void ordenaVerticesDecreciente(Eje ejeRotacion);

} ;




#endif
