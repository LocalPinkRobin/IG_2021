// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Malla3D.h
// -- declaraciones de clase Malla3D (mallas indexadas) y derivados
//
// #############################################################################

#ifndef MALLA3D_H_INCLUDED
#define MALLA3D_H_INCLUDED

#include "aux.h"

// *****************************************************************************
//
// clase para objetos 3D (mallas indexadas)
//
// *****************************************************************************

class Malla3D
{
   public:

   // dibuja el objeto en modo inmediato
   void draw_ModoInmediato();

   void draw_Ajedrez();
   // dibuja el objeto en modo diferido (usando VBOs)
   void draw_ModoDiferido();

   // función que redibuja el objeto
   // está función llama a 'draw_ModoInmediato' (modo inmediato)
   // o bien a 'draw_ModoDiferido' (modo diferido, VBOs)

   void draw(int modo_dibujado) ; //0. modo inmediat, 1. modo diferido, 2. ajedrez

   Tupla3f getColorSolido();
   Tupla3f getColorPunto();
   Tupla3f getColorLinea();
   Tupla3f getColorAj1();
   Tupla3f getColorAj2();

   //Colorear
   void colorear(const Tupla3f color);

   protected:

   void calcular_normales() ; // calcula tabla de normales de vértices (práctica 3)

   std::vector<Tupla3f> v ;   // tabla de coordenadas de vértices (una tupla por vértice, con tres floats)
   std::vector<Tupla3i> f ; // una terna de 3 enteros por cada cara o triángulo
   std::vector<Tupla3f> c ; //vector de colores

   GLuint id_vbo_ver = 0;
   GLuint id_vbo_tri = 0;

   // completar: tabla de colores, tabla de normales de vértices

   //Colores
   Tupla3f color;
   Tupla3f color_aj_1;
   Tupla3f color_aj_2;
   Tupla3f color_aristas;
   Tupla3f color_vertices;
} ;


#endif
