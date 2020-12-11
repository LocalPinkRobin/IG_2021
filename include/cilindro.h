
#ifndef CILINDRO_H_INCLUDED
#define CILINDRO_H_INCLUDED

#include "aux.h"
#include "malla.h"
#include "ply_reader.h"
#include "objrevolucion.h"

class Cilindro : public ObjRevolucion {

public:
   Cilindro(float altura, float radio,int iteraciones, bool tapa_sup=true, bool tapa_inf=true, Eje ejeRotacion = Eje::EJEY);
} ;




#endif
