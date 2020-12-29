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

void Malla3D::pintar_diferido( const std::vector<Tupla3i> & caras, bool ajedrez){
   glDrawElements (GL_TRIANGLES, 3*caras.size(), GL_UNSIGNED_INT, 0);

}

void Malla3D::pintar_inmediato( const std::vector<Tupla3i> & caras, bool ajedrez){
   glDrawElements (GL_TRIANGLES, caras.size()*3, GL_UNSIGNED_INT, caras.data());
}
// Visualización en modo inmediato con 'glDrawElements'

void Malla3D::draw_ModoInmediato(bool ajedrez)
{


   //Habilitamos el uso del array de vertices
   glEnableClientState (GL_VERTEX_ARRAY);
   glEnableClientState (GL_COLOR_ARRAY);

   if(glIsEnabled(GL_LIGHTING)){
      glEnableClientState (GL_NORMAL_ARRAY);
      glNormalPointer(GL_FLOAT,0,nv.data());
   }

   if (!ajedrez)   {

      //Indicamos el formato y la direccion de memoria del array de vertices
      // (son tuplas de 3 valoresfloat, sin espacio entre ellas)

      glVertexPointer(3,GL_FLOAT, 0, v.data());
      glColorPointer(3, GL_FLOAT, 0, c.data());

      // visualizar, indicando: tipo de primitiva, número de índices,
      // tipo de los índices, y dirección de la tabla de índices

      pintar_inmediato(f, ajedrez);
   } else{
      
         std::vector<Tupla3i> caras_pares;
         std::vector<Tupla3i> caras_impares;

         for( int i = 0; i < f.size(); i++){
            if (i%2 == 0){
               caras_pares.push_back(f[i]);
            } else {
               caras_impares.push_back(f[i]);  
            }
         }

         glVertexPointer(3, GL_FLOAT, 0, v.data());

         glColorPointer(3, GL_FLOAT, 0, c_aj1.data());

         // visualizar, indicando: tipo de primitiva, número de índices,
         // tipo de los índices, y dirección de la tabla de índices

         pintar_inmediato(caras_pares,ajedrez);
         glColorPointer(3, GL_FLOAT, 0, c_aj2.data());
         pintar_inmediato(caras_impares, ajedrez);

   }
   
   //deshabilitar array de vertices

   glDisableClientState(GL_COLOR_ARRAY);
   glDisableClientState(GL_VERTEX_ARRAY);
}

// -----------------------------------------------------------------------------
// Visualización en modo diferido con 'glDrawElements' (usando VBOs)

void Malla3D::draw_ModoDiferido(bool ajedrez)
{
   //Vertices
   glEnableClientState (GL_VERTEX_ARRAY);
   glEnableClientState (GL_COLOR_ARRAY);

   if (id_vbo_ver == 0){
      id_vbo_ver = CrearVBO(GL_ARRAY_BUFFER, v.size() * 3 * sizeof(float) , v.data() );    
   }

   glBindBuffer(GL_ARRAY_BUFFER, id_vbo_ver);
   glVertexPointer (3, GL_FLOAT, 0, 0);
   glBindBuffer (GL_ARRAY_BUFFER, 0);

   if(!ajedrez){
      //Triangulos

      if (id_vbo_tri == 0){
         id_vbo_tri = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, f.size() * 3 * sizeof(int) , f.data() );
      }

      
      id_vbo_colores = CrearVBO(GL_ARRAY_BUFFER, c.size() * 3 * sizeof(float) , c.data() );
      
   
      glBindBuffer(GL_ARRAY_BUFFER, id_vbo_colores);
      glColorPointer(3, GL_FLOAT, 0, 0);
      glBindBuffer(GL_ARRAY_BUFFER, 0);

      glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, id_vbo_tri);
      pintar_diferido(f, ajedrez);
      glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, 0);

   } else{
      
      std::vector<Tupla3i> caras_pares;
      std::vector<Tupla3i> caras_impares;

      for( int i = 0; i < f.size(); i++){
         if (i%2 == 0){
            caras_pares.push_back(f[i]);
         } else {
            caras_impares.push_back(f[i]);  
         }
      }

      if (id_vbo_tri_pares == 0){
         id_vbo_tri_pares = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, caras_pares.size() * 3 * sizeof(int) , caras_pares.data() );
      }
      if (id_vbo_tri_impares == 0){
         id_vbo_tri_impares = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, caras_impares.size() * 3 * sizeof(int) , caras_impares.data() );
      }
  
      if (id_vbo_colores_aj1 == 0){
         id_vbo_colores_aj1 = CrearVBO(GL_ARRAY_BUFFER, c_aj1.size() * 3 * sizeof(float) , c_aj1.data() );
      }

      if (id_vbo_colores_aj2 == 0){
         id_vbo_colores_aj2 = CrearVBO(GL_ARRAY_BUFFER, c_aj2.size() * 3 * sizeof(float) , c_aj2.data() );
      }

         
      glBindBuffer(GL_ARRAY_BUFFER, id_vbo_colores_aj1);
      glColorPointer(3, GL_FLOAT, 0, 0);
      glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, id_vbo_tri_pares);
      pintar_diferido(caras_pares, ajedrez);
      glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, 0);


   
      glBindBuffer(GL_ARRAY_BUFFER, id_vbo_colores_aj2);
      glColorPointer(3, GL_FLOAT, 0, 0);
      glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, id_vbo_tri_impares);
      pintar_diferido(caras_impares, ajedrez);
      glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, 0);
   }

   glDisableClientState(GL_COLOR_ARRAY);
   glDisableClientState(GL_VERTEX_ARRAY);
}
//------------------------------------------------------------------------------
void Malla3D::calcular_normales(){
   Tupla3f vA;
   Tupla3f vB;

   Tupla3f perpendicular;
   Tupla3f normal;

   nv.resize(v.size());

   for (auto it = nv.begin(); it != nv.end(); ++it){
      (*it) = {0, 0, 0};
   }

   for (auto it = f.begin(); it != f.end(); ++it){
      vA = v.at((*it)(1)) - v.at((*it)(0)) ;
      vB = v.at((*it)(2)) - v.at((*it)(0)) ;
   

   // calculo el producto vectorial para hallar la perpendicular
   // y lo normalizamos
   

   perpendicular = vA.cross(vB);

	if (perpendicular.lengthSq() > 0)
      
      normal = perpendicular.normalized();

      nv[(*it)(0)] = nv[(*it)(0)] + normal;
      nv[(*it)(1)] = nv[(*it)(1)] + normal;
      nv[(*it)(2)] = nv[(*it)(2)] + normal;

   }

   for (auto it = nv.begin(); it != nv.end(); ++it){
      if ((*it).lengthSq() > 0)
         (*it) = (*it).normalized();
   }
}


// -----------------------------------------------------------------------------
// Función de visualización de la malla,
// puede llamar a  draw_ModoInmediato o bien a draw_ModoDiferido

void Malla3D::draw(int modo_dibujado, bool ajedrez) 
{
   if (modo_dibujado == 0){
      draw_ModoInmediato(ajedrez);
   } else if (modo_dibujado == 1){
      draw_ModoDiferido(ajedrez);
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

void Malla3D::colorear(int tipo){
    //0. Solido, 1. puntos, 2. rayas, 3. ajedrez
   if(tipo == 0){
      c = std::vector<Tupla3f>(v.size(), color);
   } else if(tipo == 1){
      c = std::vector<Tupla3f>(v.size(), color_vertices);
   } else if(tipo == 2){
      c = std::vector<Tupla3f>(v.size(), color_aristas);
   } else if (tipo == 3){
      c_aj1 = std::vector<Tupla3f>(v.size(), color_aj_1);
      c_aj2 = std::vector<Tupla3f>(v.size(), color_aj_2);

   }
}
