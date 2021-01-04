

#include "aux.h"     // includes de OpenGL/glut/glew, windows, y librería std de C++
#include "escena.h"
#include "malla.h" // objetos: Cubo y otros....
#include "objply.h"


//**************************************************************************
// constructor de la escena (no puede usar ordenes de OpenGL)
//**************************************************************************

Escena::Escena()
{
    Front_plane       = 50.0;
    Back_plane        = 2000.0;
    Observer_distance = 4*Front_plane;
    Observer_angle_x  = 0.0 ;
    Observer_angle_y  = 0.0 ;

    ejes.changeAxisSize( 5000 );

    // crear los objetos de la escena....
    // .......completar: ...
    // .....

    cubo = new Cubo(50);
    tetraedro = new Tetraedro(50);
    objetoply = new ObjPLY("./plys/peach.ply");
    cono = new Cono(50,20,50,Eje::EJEX);
    bola = new Esfera(25, 50,50, true, true);
    cilindro = new Cilindro( 50, 25, 50,true, true, Eje::EJEZ); 
    peon_blanco = new ObjRevolucion("./plys/peon.ply", 50,true,true,Eje::EJEY);
    peon_negro = new ObjRevolucion("./plys/peon.ply", 50,true,true,Eje::EJEY);


    int num_obj = 8; // 0. peon 1. peon

   visibilidad_objetos.resize(num_obj);
   visibilidad_objetos [0] = false;
   visibilidad_objetos [1] = false;
   visibilidad_objetos [2] = false;
   visibilidad_objetos [3] = true;
   visibilidad_objetos [4] = false;
   visibilidad_objetos [5] = false;
   visibilidad_objetos [6] = false;
   visibilidad_objetos [7] = true;
   


   visualizacion_dibujado.resize(4); //0. Solido, 1. puntos, 2. rayas, 3. ajedrez
   visualizacion_dibujado [0] = true;
   visualizacion_dibujado [1] = false;
   visualizacion_dibujado [2] = false;
   visualizacion_dibujado [3] = false;;

   modo_dibujado = 0;

   Tupla4f difuso = {255/255.0f, 255/255.0f, 255/255.0f, 1.0f};
   Tupla4f especular = {255/255.0f, 255/255.0f, 255/255.0f,1.0f};
   Tupla4f ambiente ={255/255.0f, 255/255.0f, 255/255.0f,1.0f};

   Tupla3f posicion = {50.0f,50.0f,50.0f};

   posicional  = new LuzPosicional (posicion, GL_LIGHT0,  {0, 0, 0, 1}, {1,1,1,1}, {1,1,1,1});
   direccional = new LuzDireccional ( posicion, GL_LIGHT1, {0, 0, 0, 1}, {1,1,1,1}, {1,1,1,1});

   Material caucho_blanco ({0.05, 0.05, 0.05,1},{0.05, 0.05, 0.05,1}, {0.07, 0.07, 0.07,1},0.078125*128.0f );
   Material oro ({0.24725, 0.1995, 0.0745, 1}, {0.75164, 0.60648, 0.22648, 1}, {0.628281, 0.555802, 0.366065, 1}, 0.4*128.0f);
   Material oro_rosa ({0.24725, 0.1995, 0.0745, 1}, {255.0/255, 179.0/255, 209.0/255, 1}, {0.628281, 0.555802, 0.366065, 1}, 0.4*128.0f);
   Material ruby({0.1745, 0.01175, 0.01175, 1}, {0.61424, 0.04136, 0.04136, 1}, {0.727811, 0.626959, 0.626959, 1}, 128.0f * 0.6f );
   Material perla({0.25, 0.20725, 0.20725, 1}, {1, 0.829, 0.829, 1}, {0.296648, 0.296648, 0.296648, 1}, 128.0f * 0.088);
   Material esmeralda({0.0215, 0.1745, 0.0215, 1}, {0.07568, 0.61424, 0.07568, 1}, {0.633, 0.727811,0.633, 1}, 0.6 * 128.0f);
   Material plata({0.19225, 0.19225, 0.19225, 1}, {0.50754, 0.50754, 0.50754, 1}, {0.508273,0.508273, 0.508273, 1}, 0.4*128.0f);
   Material turquesa({0.1, 0.18725, 0.1745, 1}, {0.396, 0.74151, 0.69102, 1}, {0.297254, 0.30829, 0.306678, 1} ,0.1 * 128.0f);

   Material difuse({0.0f, 0.0f, 0.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 0.0f, 1.0f}, 128.0f);
   Material specular({0.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, 128.0f);

   peon_negro->setMaterial(specular);
   peon_blanco->setMaterial(difuse);
   objetoply->setMaterial(oro_rosa);

}

//**************************************************************************
// inicialización de la escena (se ejecuta cuando ya se ha creado la ventana, por
// tanto sí puede ejecutar ordenes de OpenGL)
// Principalmemnte, inicializa OpenGL y la transf. de vista y proyección
//**************************************************************************

void Escena::inicializar( int UI_window_width, int UI_window_height )
{
	glClearColor( 1.0, 1.0, 1.0, 1.0 );// se indica cual sera el color para limpiar la ventana	(r,v,a,al)

	glEnable( GL_DEPTH_TEST );	// se habilita el z-bufer
   glEnable( GL_CULL_FACE );
   glEnable( GL_NORMALIZE );


	Width  = UI_window_width/10;
	Height = UI_window_height/10;

   change_projection( float(UI_window_width)/float(UI_window_height) );
	glViewport( 0, 0, UI_window_width, UI_window_height );
}



// **************************************************************************
//
// función de dibujo de la escena: limpia ventana, fija cámara, dibuja ejes,
// y dibuja los objetos
//
// **************************************************************************

void Escena::dibujar()
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Limpiar la pantalla
	change_observer();
   if(posicional != nullptr){
      posicional->activar();
   }

   if(direccional != nullptr){
      direccional->activar();
   }
    if (glIsEnabled(GL_LIGHTING)){
       glDisable(GL_LIGHTING);
       ejes.draw();
       glEnable(GL_LIGHTING);

    } else{
      ejes.draw();
    }
    // COMPLETAR
    //   Dibujar los diferentes elementos de la escena
    // Habrá que tener en esta primera práctica una variable que indique qué objeto se ha de visualizar
    // y hacer 
    if(visualizacion_dibujado[0]){
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      dibujarObjeto(GL_FILL);
      
    }

    if (visualizacion_dibujado[1]){
      glPointSize(6);
      glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
      dibujarObjeto(GL_POINT);
    }

   if (visualizacion_dibujado[2]){
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
      dibujarObjeto(GL_LINE);
   }
   if (visualizacion_dibujado[3]){
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      dibujarObjeto(GL_FILL);
   }
   
}

void Escena::dibujarObjeto(GLenum modo){
   int num_dibujado;

   if (modo == GL_FILL){
      num_dibujado = 0;

   } else if (modo == GL_POINT){
      num_dibujado = 1;

   } else if (modo == GL_LINE){
      
      num_dibujado = 2;
   }
   
   if (cubo != nullptr){
      cubo->colorear(num_dibujado);
   }
   if (tetraedro != nullptr){
      tetraedro->colorear(num_dibujado);
   }
   if (objetoply != nullptr){
      objetoply->colorear(num_dibujado);
   }
   if (peon_blanco != nullptr){
      peon_blanco -> colorear(num_dibujado);
   }
   if (peon_negro != nullptr){
      peon_negro -> colorear(num_dibujado);
   }
   if (cilindro != nullptr){
      cilindro-> colorear(num_dibujado);
   }
   if (cono != nullptr){
      cono -> colorear(num_dibujado);
   }
   if (bola != nullptr){
      bola-> colorear(num_dibujado);
   }

   if (cubo != nullptr && visibilidad_objetos[0]){
      glPushMatrix();
         glTranslatef(100.0,0.0, 0.0);
         cubo->draw(modo_dibujado, visualizacion_dibujado[3]);
      glPopMatrix();

   }

   if (tetraedro != nullptr && visibilidad_objetos[1]){
      glPushMatrix();
         glTranslatef(-100.0,0.0, 0.0);
         tetraedro->draw(modo_dibujado, visualizacion_dibujado[3]);
      glPopMatrix();

   }

   if (objetoply != nullptr && visibilidad_objetos[2]){
      glPushMatrix();
         glTranslatef(100.0,0.0, 0.0);
         glScalef(10.0, 10.0, 10.0);
         objetoply->draw(modo_dibujado, visualizacion_dibujado[3]);
      glPopMatrix();

   }

   if (peon_blanco != nullptr && visibilidad_objetos[7]){

      glPushMatrix();
         glTranslatef(100.0,0.0, 0.0);
         glScalef(20.0, 20.0, 20.0);
         peon_blanco->draw(modo_dibujado, visualizacion_dibujado[3]);
      glPopMatrix();
   }
   if (peon_negro != nullptr && visibilidad_objetos[3]){

      glPushMatrix();
         glScalef(20.0, 20.0, 20.0);
         peon_negro->draw(modo_dibujado, visualizacion_dibujado[3]);
      glPopMatrix();
   }

   if (cilindro != nullptr && visibilidad_objetos[4]){
         cilindro->draw(modo_dibujado, visualizacion_dibujado[3]);
   }

   if (cono != nullptr && visibilidad_objetos[5]){
         cono->draw(modo_dibujado, visualizacion_dibujado[3]);
   }
   
   if (bola != nullptr && visibilidad_objetos[6]){
         bola->draw(modo_dibujado, visualizacion_dibujado[3]);
   }


}

//**************************************************************************
//
// función que se invoca cuando se pulsa una tecla
// Devuelve true si se ha pulsado la tecla para terminar el programa (Q),
// devuelve false en otro caso.
//
//**************************************************************************

bool Escena::teclaPulsada( unsigned char tecla, int x, int y )
{
   using namespace std ;
   cout << "Tecla pulsada: '" << tecla << "'" << endl;
   bool salir=false;
   switch( toupper(tecla) )
   {
      case 'Q' :
         if (modoMenu!=NADA) {
            modoMenu=NADA;            
            cout << "V --> Entrar en modo visualización" << endl
                 << "O --> Entrar en modo seleccion objeto" << endl
                 << "D --> Entrar en modo de dibujado"<< endl
                 << "A --> Modificar alfa (si luz encendida)"<< endl
                 << "B --> Modificar beta (si luz encendida)"<< endl;
            }
         else {
            salir=true ;
         }
         break ;

      case 'X' :
         if (glIsEnabled(GL_LIGHTING)){
            if(sombreado == GL_SMOOTH){
               sombreado = GL_FLAT;
               cout << "Dibujando en modo FLAT" << endl;
            } else{
               sombreado = GL_SMOOTH;
               cout << "Dibujando en modo SMOOTH" << endl;

            }
            glShadeModel(sombreado);
         }
      break ;

      case 'O' :
         // ESTAMOS EN MODO SELECCION DE OBJETO
         modoMenu=SELOBJETO;
         cout << "Modo seleccion objeto" << endl;
         cout << "C --> Visualizar/ocultar Cubo" << endl
              << "T --> Visualizar/ocultar Tetraedro"<< endl
              << "Y --> Visualizar/ocultar ObjetoPly" << endl
              << "W --> Visualizar/ocultar objeto de revolucion" << endl
              << "R --> Visualizar/ocultar Cilindro"<< endl
              << "N --> Visualizar/ocultar Cono"<< endl
              << "E --> Visualizar/ocultar Esfera"<< endl
              << "U ->> Visualizar/ocultar el otro peon" << endl
              << "Q --> Quitar modo seleccion de objeto" << endl;
         break ;
      case 'C':
         if(modoMenu == SELOBJETO){
            visibilidad_objetos[0] = !visibilidad_objetos[0];
         }
         break ;

      case 'T':
         if(modoMenu == SELOBJETO){
            visibilidad_objetos[1] = !visibilidad_objetos[1];
         } else if(modoMenu == SELVISUALIZACION) {
            
            if (peon_blanco != nullptr){
               peon_blanco ->dibujar_tapas(!peon_blanco->getMostrarTapas());
            }
            if (peon_negro != nullptr){
               peon_negro ->dibujar_tapas(!peon_negro->getMostrarTapas());
            } 
            if (cilindro != nullptr){
               cilindro->dibujar_tapas(!cilindro->getMostrarTapas());
            }
            if (cono != nullptr){
               cono -> dibujar_tapas(!cono->getMostrarTapas());
            }
            if (bola != nullptr){
               bola-> dibujar_tapas(!bola->getMostrarTapas());
            }
         }
         break ;

         case 'Y':
         if(modoMenu == SELOBJETO){
            visibilidad_objetos[2] = !visibilidad_objetos[2];
         }
         break ;

         case 'W':
         if(modoMenu == SELOBJETO){
            visibilidad_objetos[3] = !visibilidad_objetos[3];
         }
         break ;

         case 'R':
         if(modoMenu == SELOBJETO){
            visibilidad_objetos[4] = !visibilidad_objetos[4];
         }
         break ;

         case 'N':
         if(modoMenu == SELOBJETO){
            visibilidad_objetos[5] = !visibilidad_objetos[5];
         }
         break ;

         case 'E':
         if(modoMenu == SELOBJETO){
            visibilidad_objetos[6] = !visibilidad_objetos[6];
         }

         case 'U':
         if(modoMenu == SELOBJETO){
            visibilidad_objetos[7] = !visibilidad_objetos[7];
         }
         break ;
      case 'V' :
         // ESTAMOS EN MODO SELECCION DE MODO DE VISUALIZACION
         if(modoMenu == NADA){
            modoMenu=SELVISUALIZACION;
            cout << "Modo visualizacion" << endl;
            cout << "P --> Modo puntos" << endl
                 << "L --> Modo lineas" << endl
                 << "S --> Modo solido" << endl
                 << "A --> Modo Ajedrez" << endl
                 << "T --> Mostrar/Quitar tapas" << endl
                 << "I --> Activar/desactivar iluminacion" << endl
                 << "Q --> Quitar modo seleccion de visualizacion" << endl;
         }
         break ;
       case 'I' :
         if (modoMenu == SELVISUALIZACION){
            if (glIsEnabled(GL_LIGHTING)){
               glDisable(GL_LIGHTING);
            } else {
               glEnable(GL_LIGHTING);
               cout << "0 --> Iluminacion posicional" << endl 
                    << "1 --> Iluminacion direccional" << endl;

            }
         }
       break;
       
       case 'D' :
         // ESTAMOS EN MODO SELECCION DE DIBUJADO
         modoMenu=SELDIBUJADO;
         cout << "Actualizar el modo de dibujado" << endl;
         cout << "1 --> Modo glDrawElements"<< endl
              << "2 --> Modo diferido"<< endl
              << "Q --> Quitar modo seleccion de dibujado" << endl;

         break ;

         case '0':
            if(glIsEnabled(GL_LIGHTING)){
               if(glIsEnabled(GL_LIGHT0)){
                  glDisable(GL_LIGHT0);
               }else{
                  cout << "Encendida luz posicional" << endl;
                  glEnable(GL_LIGHT0);
               }
            }
         break;
         
         case '1':
         if( modoMenu==SELDIBUJADO ){
            modo_dibujado = 0;
            cout << "Dibujando en modo inmediato";
         } else if (modoMenu==SELVISUALIZACION){
            if(glIsEnabled(GL_LIGHTING)){
               if(glIsEnabled(GL_LIGHT1)){
                  glDisable(GL_LIGHT1);
               }else{
                  cout << "Encendida luz direccional" << endl;
                  glEnable(GL_LIGHT1);
               }
            }
         }
         break;
         case '2':
            if(modoMenu==SELDIBUJADO){
               modo_dibujado = 1;
               cout << "Dibujando en modo diferido";
            }
         break;
         case 'A':
            if (modoMenu == SELVISUALIZACION){
               visualizacion_dibujado[3] = true;
               visualizacion_dibujado[0] = false;
               visualizacion_dibujado[1] = false;
               visualizacion_dibujado[2] = false;
               visualizacion_dibujado[4] = false;
               visualizacion_dibujado[5] = false;

               cout << "Dibujando en modo ajedrez";
            } else if (modoMenu == NADA && glIsEnabled(GL_LIGHTING)){
               cout << "Cambiar angulo ALFA" << endl;
               modoMenu = V_ALFA;
            }
         break;
      case 'B': //MODO PUNTOS
         if (modoMenu == NADA && glIsEnabled(GL_LIGHTING)){
               cout << "Cambiar angulo BETA" << endl;
               modoMenu = V_BETA;
            }
      break;

      case '<':
         if (modoMenu == V_ALFA) {
            cout << "Disminuyendo angulo ALFA" << endl;
            direccional->variarAnguloAlpha(-5*SEXA_TO_RAD);
         } else if(modoMenu == V_BETA){
            cout << "Disminuyendo angulo BETA" << endl;

            direccional->variarAnguloBeta(-5*SEXA_TO_RAD);
         }
      break;

      case '>':
         if (modoMenu == V_ALFA) {
            cout << "Aumentando angulo ALFA" << endl;

            direccional->variarAnguloAlpha(5*SEXA_TO_RAD);
         } else if (modoMenu == V_BETA){
            cout << "Aumentando angulo BETA" << endl;

            direccional->variarAnguloBeta(5*SEXA_TO_RAD);
         }
      break;

         // COMPLETAR con los diferentes opciones de teclado
      case 'P': //MODO PUNTOS
         if(modoMenu == SELVISUALIZACION){
            visualizacion_dibujado[1] = !visualizacion_dibujado[1];
            visualizacion_dibujado[3] = false;
            cout << "Actualizado modo punto" << endl;
         } 
         break;
      case 'L': //MODO LINEAS
         if(modoMenu == SELVISUALIZACION){
            visualizacion_dibujado[2] = !visualizacion_dibujado[2];
            visualizacion_dibujado[3] = false;
            cout << "Actualizado modo linea" << endl;
         }
         break;
      case 'S': //MODO SOLIDO
         if(modoMenu == SELVISUALIZACION){
            visualizacion_dibujado[0] = !visualizacion_dibujado[0];
            visualizacion_dibujado[3] = false;
            cout << "Actualizado modo solido" << endl;
         }
         break;


      
            
   }
   return salir;
}
//**************************************************************************

void Escena::teclaEspecial( int Tecla1, int x, int y )
{
   switch ( Tecla1 )
   {
	   case GLUT_KEY_LEFT:
         Observer_angle_y-- ;
         break;
	   case GLUT_KEY_RIGHT:
         Observer_angle_y++ ;
         break;
	   case GLUT_KEY_UP:
         Observer_angle_x-- ;
         break;
	   case GLUT_KEY_DOWN:
         Observer_angle_x++ ;
         break;
	   case GLUT_KEY_PAGE_UP:
         Observer_distance *=1.2 ;
         break;
	   case GLUT_KEY_PAGE_DOWN:
         Observer_distance /= 1.2 ;
         break;
	}

	//std::cout << Observer_distance << std::endl;
}

//**************************************************************************
// Funcion para definir la transformación de proyeccion
//
// ratio_xy : relacción de aspecto del viewport ( == ancho(X) / alto(Y) )
//
//***************************************************************************

void Escena::change_projection( const float ratio_xy )
{
   glMatrixMode( GL_PROJECTION );
   glLoadIdentity();
   const float wx = float(Height)*ratio_xy ;
   glFrustum( -wx, wx, -Height, Height, Front_plane, Back_plane );
}
//**************************************************************************
// Funcion que se invoca cuando cambia el tamaño de la ventana
//**************************************************************************

void Escena::redimensionar( int newWidth, int newHeight )
{
   Width  = newWidth/10;
   Height = newHeight/10;
   change_projection( float(newHeight)/float(newWidth) );
   glViewport( 0, 0, newWidth, newHeight );
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void Escena::change_observer()
{
   // posicion del observador
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef( 0.0, 0.0, -Observer_distance );
   glRotatef( Observer_angle_y, 0.0 ,1.0, 0.0 );
   glRotatef( Observer_angle_x, 1.0, 0.0, 0.0 );
}
