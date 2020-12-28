
#ifndef ESFERA_H_INCLUDED
#define ESFERA_H_INCLUDED

#include "aux.h"
#include "malla.h"
#include "ply_reader.h"
#include "objrevolucion.h"

class Esfera : public ObjRevolucion {

public:
   Esfera(float radio, int iteraciones, int num_vert_perfil, bool tapa_sup, bool tapa_inf);
} ;




#endif
