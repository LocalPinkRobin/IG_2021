#include "objply.h"
#include "ply_reader.h"
 

// *****************************************************************************
//
// Clase ObjPLY (práctica 2)
//
// *****************************************************************************

ObjPLY::ObjPLY( const std::string & nombre_archivo )
{
   // leer la lista de caras y vértices
   ply::read( nombre_archivo, this->v, this->f );
   
   c.resize(v.size());  //Los colores cambian cada vez que dibujamos por si cambiamos la forma de visualizacion
   c_aj1.resize(v.size());
   c_aj2.resize(v.size());

   calcular_normales();
   
   color = {69/255.0, 245/255.0, 186/255.0};
   color_aj_1 = {1.0, 0.6, 0.8};
      color_aj_2 = {0.0, 0.0, 0.0};
   color_aristas = {1,0,0};
   color_vertices = {0,0,1};

   
   colorear(0);
   colorear(3);
}


