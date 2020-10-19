#include "aux.h"
#include "malla.h"
#include "tetraedro.h"

Tetraedro::Tetraedro(float lado)
{

   float mediana = sqrt( pow(lado,2) - pow(lado/2, 2) );
   float altura = sqrt( pow(lado,2) - pow(mediana/3, 2) ) ;


   // inicializar la tabla de vértices
   
   v.resize(4);

   v[0] = {0,0,0};
   v[1]= {lado, 0, 0}; // punto en eje x
   v[2]= {lado/2, 0, mediana};

   // vertice superior
   v[3]= {lado/2, altura, mediana/3};



    
   // inicializar la tabla de caras o triángulos:

   f.resize(12);

   f[0] = {3, 2, 1};
   f[1] = {0, 3, 1};
   f[2] = {2, 3, 0};
   f[3] = {1, 2, 0};
   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)
   
   //Coloreado
   c.resize(v.size());  //Los colores cambian cada vez que dibujamos por si cambiamos la forma de visualizacion

   color = {69/255.0, 245/255.0, 186/255.0};
   color_aj_1 = {1.0, 0.6, 0.8};
   color_aj_2 = {201/255.0, 181/255.0, 191/255.0};
   color_aristas = {1,0,0};
   color_vertices = {0,0,1};

   colorear(color);
}

