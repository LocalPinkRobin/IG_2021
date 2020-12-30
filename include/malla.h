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

#include "material.h"
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
   void draw_ModoInmediato(bool ajedrez);
   void draw_ModoDiferido(bool ajedrez);

   // función que redibuja el objeto
   // está función llama a 'draw_ModoInmediato' (modo inmediato)
   // o bien a 'draw_ModoDiferido' (modo diferido, VBOs)

   void draw(int modo_dibujado, bool ajedrez) ; //0. modo inmediat, 1. modo diferido

   Tupla3f getColorSolido();
   Tupla3f getColorPunto();
   Tupla3f getColorLinea();
   Tupla3f getColorAj1();
   Tupla3f getColorAj2();

   //Colorear
   void colorear(int tipo);
   
   void setMaterial (const Material & m);

   protected:

   Material m;

   void calcular_normales() ; // calcula tabla de normales de vértices (práctica 3)
   virtual void pintar_diferido( const std::vector<Tupla3i> & caras, bool ajedrez);
   virtual void pintar_inmediato( const std::vector<Tupla3i> & caras, bool ajedrez);

   std::vector<Tupla3f> v ;   // tabla de coordenadas de vértices (una tupla por vértice, con tres floats)
   std::vector<Tupla3i> f ; // una terna de 3 enteros por cada cara o triángulo
   std::vector<Tupla3f> nv; //tupla de 3 reales que representa el vector perpendicular a la superficie de la malla en el vertice
   std::vector<Tupla3f> c ; //vector de colores
   std::vector<Tupla3f> c_aj1 ; //vector de colores
   std::vector<Tupla3f> c_aj2 ; //vector de colores

   GLuint id_vbo_nor = 0;
   GLuint id_vbo_ver = 0;
   GLuint id_vbo_colores = 0;
   GLuint id_vbo_colores_aj1 = 0;
   GLuint id_vbo_colores_aj2 = 0;

   GLuint id_vbo_tri = 0;
   GLuint id_vbo_tri_pares = 0;
   GLuint id_vbo_tri_impares = 0;

   // completar: tabla de colores, tabla de normales de vértices

   //Colores
   Tupla3f color;
   Tupla3f color_aj_1;
   Tupla3f color_aj_2;
   Tupla3f color_aristas;
   Tupla3f color_vertices;
} ;


#endif
