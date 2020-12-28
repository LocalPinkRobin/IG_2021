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
    void dibujar_tapas (bool dibujar);
    bool getMostrarTapas();

protected:
    int iteraciones;

    bool mostrar_tapas = true;

    virtual void pintar_diferido( const std::vector<Tupla3i> & caras, bool ajedrez);
    virtual void pintar_inmediato(const std::vector<Tupla3i> & caras, bool ajedrez);

    Tupla3f v_superior, v_inferior;

    bool mostrarTapas, tapaSuperior, tapaInferior;

    void generarVertices(int iteraciones,Eje ejeRotacion);
    Tupla3f rotarVertice (Tupla3f vertice, double angulo, Eje ejeRotacion);

    void ordenaVerticesDecreciente(Eje ejeRotacion);
    void generarTriangulos(int iteraciones);

    std::vector<Tupla3f> vectorOriginal;

    void crearMalla (const std::vector<Tupla3f> & perfil_original,
                     const int num_instancias_perf,
                     Eje ejeRotacion = Eje::EJEY);

} ;




#endif
