#include "aux.h"
#include "malla.h"
#include "cubo.h"

Cubo::Cubo(float lado)
{

   // inicializar la tabla de vértices

   v.resize(8);

   v[0] = {0,0,0};
   v[1] = {0,0, lado};;
   v[2] = {lado, 0, lado};
   v[3] = {lado, 0, 0};

   v[4] = {0,lado,0};
   v[5] = {0,lado, lado};;
   v[6] = {lado, lado, lado};
   v[7] = {lado, lado, 0};



   // inicializar la tabla de caras o triángulos:

   f.resize(12);

//Cara inferior
   f[0] = {0, 4, 7};
   f[1] = {7, 3, 0};

   f[2] = {3, 7, 6};
   f[3] = {6, 2, 3};

   f[4] = {2, 6, 1};
   f[5] = {1, 6, 5};

   f[6] = {5, 0, 1};
   f[7] = {4, 0, 5};

   f[8] = {0, 3, 2};
   f[9] = {1, 0, 2};

   f[10] = {4, 5, 6};
   f[11] = {6, 7, 4};
   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)
   
   c.resize(v.size());  //Los colores cambian cada vez que dibujamos por si cambiamos la forma de visualizacion

   color = {69/255.0, 245/255.0, 186/255.0};
   color_aj_1 = {1.0, 0.6, 0.8};
   color_aj_2 = {201/255.0, 181/255.0, 191/255.0};
   color_aristas = {1,0,0};
   color_vertices = {0,0,1};

   colorear(color);

}

