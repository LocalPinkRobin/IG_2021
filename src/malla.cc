#include "aux.h"
#include "malla.h"

// *****************************************************************************
//
// Clase Malla3D
//
// *****************************************************************************

//Creacion de VBOs

GLuint CrearVBO (GLuint tipo_vbo, GLuint tamanio_bytes, GLvoid * puntero_ram){
   GLuint id_vbo;
   glGenBuffers (1, & id_vbo);

   glBindBuffer (tipo_vbo, id_vbo);

   glBufferData(tipo_vbo,tamanio_bytes, puntero_ram, GL_STATIC_DRAW);

   glBindBuffer(tipo_vbo, 0);
   return id_vbo;
}


// Visualización en modo inmediato con 'glDrawElements'

void Malla3D::draw_ModoInmediato()
{

   //Habilitamos el uso del array de vertices
   glEnableClientState (GL_VERTEX_ARRAY);
   glEnableClientState (GL_COLOR_ARRAY);

   //Indicamos el formato y la direccion de memoria del array de vertices
   // (son tuplas de 3 valoresfloat, sin espacio entre ellas)

   glVertexPointer(3,GL_FLOAT, 0, v.data());
   glColorPointer(3, GL_FLOAT, 0, c.data());

   // visualizar, indicando: tipo de primitiva, número de índices,
   // tipo de los índices, y dirección de la tabla de índices

   glDrawElements (GL_TRIANGLES, f.size()*3, GL_UNSIGNED_INT, f.data());

   //deshabilitar array de vertices

   glDisableClientState(GL_COLOR_ARRAY);
   
   glDisableClientState(GL_VERTEX_ARRAY);
   



}

void Malla3D::draw_Ajedrez() {


   std::vector<Tupla3i> caras_pares;
   std::vector<Tupla3i> caras_impares;

   for( int i = 0; i < f.size(); i++){
      if (i%2 == 0){
         caras_pares.push_back(f[i]);
      } else {
         caras_impares.push_back(f[i]);  
      }
   }

   //Habilitamos el uso del array de vertices
   glEnableClientState (GL_VERTEX_ARRAY);
   glEnableClientState (GL_COLOR_ARRAY);

   //Indicamos el formato y la direccion de memoria del array de vertices
   // (son tuplas de 3 valoresfloat, sin espacio entre ellas)

   glVertexPointer(3,GL_FLOAT, 0, v.data());

   colorear(getColorAj1());
   glColorPointer(3, GL_FLOAT, 0, c.data());

   // visualizar, indicando: tipo de primitiva, número de índices,
   // tipo de los índices, y dirección de la tabla de índices

   glDrawElements (GL_TRIANGLES, caras_pares.size()*3, GL_UNSIGNED_INT, caras_pares.data());

   colorear(getColorAj2());
   glColorPointer(3, GL_FLOAT, 0, c.data());
   glDrawElements (GL_TRIANGLES, caras_impares.size()*3, GL_UNSIGNED_INT, caras_impares.data());


   //deshabilitar array de vertices

   glDisableClientState(GL_COLOR_ARRAY);
   
   glDisableClientState(GL_VERTEX_ARRAY);
   



}
// -----------------------------------------------------------------------------
// Visualización en modo diferido con 'glDrawElements' (usando VBOs)

void Malla3D::draw_ModoDiferido()
{
   //Vertices


   if (id_vbo_ver == 0){
      id_vbo_ver = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, f.size() * 3 * sizeof(int) , v.data() );
   }

   glBindBuffer(GL_ARRAY_BUFFER, id_vbo_ver);
   glVertexPointer (3, GL_FLOAT, 0, 0);
   glBindBuffer (GL_ARRAY_BUFFER, 0);
   glEnableClientState(GL_VERTEX_ARRAY);

   //Triangulos

   if (id_vbo_tri == 0){
      id_vbo_tri = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, f.size() * 3 * sizeof(int) , f.data() );
   }

   glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, id_vbo_tri);
   glDrawElements (GL_TRIANGLES, 3*f.size(), GL_UNSIGNED_INT, 0);
   glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, 0);

   glDisableClientState(GL_VERTEX_ARRAY);



}
// -----------------------------------------------------------------------------
// Función de visualización de la malla,
// puede llamar a  draw_ModoInmediato o bien a draw_ModoDiferido

void Malla3D::draw(int modo_dibujado) 
{
   if (modo_dibujado == 0){
      draw_ModoInmediato();
   } else if (modo_dibujado == 1){
      draw_ModoDiferido();
   } else if (modo_dibujado == 2){
      draw_Ajedrez();
   }

}
Tupla3f Malla3D::getColorSolido(){
   return (color);
}

Tupla3f Malla3D::getColorPunto(){
   return (color_vertices);
}
Tupla3f Malla3D::getColorLinea(){
   return (color_aristas);
}
Tupla3f Malla3D::getColorAj1(){
   return (color_aj_1);

}
Tupla3f Malla3D::getColorAj2(){
   return (color_aj_2);

}

//Funcion de colorear

void Malla3D::colorear(const Tupla3f color){

   c = std::vector<Tupla3f>(v.size(), color);
}
