
#ifndef CONO_H_INCLUDED
#define CONO_H_INCLUDED

#include "aux.h"
#include "malla.h"
#include "ply_reader.h"
#include "objrevolucion.h"

class Cono : public ObjRevolucion {

public:
   Cono(float altura, float radio,int iteraciones, Eje ejeRotacion = Eje::EJEY);
} ;




#endif
