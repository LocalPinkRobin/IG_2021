

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
    objetoply = new ObjPLY("./plys/beethoven.ply");
    peon = new ObjRevolucion("./plys/peon.ply" , 50,false,true);

    int num_obj = 4; // 0. Cubo 1. Tetraedro 2.Beethoven

   visibilidad_objetos.resize(num_obj);
   visibilidad_objetos [0] = false;
   visibilidad_objetos [1] = false;
   visibilidad_objetos [2] = false;
   visibilidad_objetos [3] = true;


   modos_dibujado.resize(4); //0. Solido, 1. puntos, 2. rayas, 3. ajedrez
   modos_dibujado [0] = true;
   modos_dibujado [1] = false;
   modos_dibujado [2] = false;
   modos_dibujado [3] = false;

   modo_dibujado = 0;

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
    ejes.draw();
    // COMPLETAR
    //   Dibujar los diferentes elementos de la escena
    // Habrá que tener en esta primera práctica una variable que indique qué objeto se ha de visualizar
    // y hacer 
    if(modos_dibujado[0]){
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      dibujarObjeto(GL_FILL);
      
    }

    if (modos_dibujado[1]){
      glPointSize(6);
      glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
      dibujarObjeto(GL_POINT);
    }

   if (modos_dibujado[2]){
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
      dibujarObjeto(GL_LINE);
   }
   if (modos_dibujado[3]){
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      dibujarObjeto(GL_FILL);
   }
   
}

void Escena::dibujarObjeto(GLenum modo){

   if (modo == GL_FILL){
      cubo->colorear(0);
      tetraedro->colorear(0);
      objetoply->colorear(0);
   } else if (modo == GL_POINT){
      cubo->colorear(1);
      tetraedro->colorear(1); 
      objetoply->colorear(1);      
   } else if (modo == GL_LINE){
      
      cubo->colorear(2);
      tetraedro->colorear(2);   
      objetoply->colorear(2); 
   }

   if (cubo != nullptr && visibilidad_objetos[0]){
      cubo->draw(modo_dibujado, modos_dibujado[3]);
   }

   if (tetraedro != nullptr && visibilidad_objetos[1]){
      tetraedro->draw(modo_dibujado, modos_dibujado[3]);
   }

   if (objetoply != nullptr && visibilidad_objetos[2]){
      objetoply->draw(modo_dibujado, modos_dibujado[3]);
   }

   if (peon != nullptr && visibilidad_objetos[3]){

      glPushMatrix();
         glScalef(20.0, 20.0, 20.0);
         peon->draw(modo_dibujado, modos_dibujado[3]);
      glPopMatrix();
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
         if (modoMenu!=NADA)
            modoMenu=NADA;            
         else {
            salir=true ;
         }
         break ;
      case 'O' :
         // ESTAMOS EN MODO SELECCION DE OBJETO
         modoMenu=SELOBJETO;
         cout << "Modo seleccion objeto" << endl;
         cout << "C --> Visualizar/ocultar Cubo" << endl
              << "T --> Visualizar/ocultar Tetraedro"<< endl
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
         }
         break ;
      case 'V' :
         // ESTAMOS EN MODO SELECCION DE MODO DE VISUALIZACION
         modoMenu=SELVISUALIZACION;
         cout << "Modo visualizacion" << endl;
         cout << "P --> Modo puntos" << endl
              << "L --> Modo lineas"<< endl
              << "S --> Modo solido"<< endl
              << "A --> Modo Ajedrez"<< endl
              << "Q --> Quitar modo seleccion de visualizacion" << endl;

         break ;
       case 'D' :
         // ESTAMOS EN MODO SELECCION DE DIBUJADO
         modoMenu=SELDIBUJADO;
         cout << "Actualizar el modo de dibujado" << endl;
         cout << "1 --> Modo glDrawElements"<< endl
              << "2 --> Modo diferido"<< endl
              << "Q --> Quitar modo seleccion de dibujado" << endl;

         break ;

         case '1':
         if( modoMenu==SELDIBUJADO ){
            modo_dibujado = 0;
            cout << "Dibujando en modo inmediato";
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
               modos_dibujado[3] = true;
               modos_dibujado[0] = false;
               modos_dibujado[1] = false;
               modos_dibujado[2] = false;

               cout << "Dibujando en modo ajedrez";
            }
         break;
         // COMPLETAR con los diferentes opciones de teclado
      case 'P': //MODO PUNTOS
         if(modoMenu == SELVISUALIZACION){
            modo_dibujado = 0;
            modos_dibujado[1] = !modos_dibujado[1];
            modos_dibujado[3] = false;
            cout << "Actualizado modo punto" << endl;
         }
         break;
      case 'L': //MODO LINEAS
         if(modoMenu == SELVISUALIZACION){
            modo_dibujado = 0;
            modos_dibujado[2] = !modos_dibujado[2];
            modos_dibujado[3] = false;
            cout << "Actualizado modo linea" << endl;
         }      
         break;
      case 'S': //MODO SOLIDO
         if(modoMenu == SELVISUALIZACION){
            modo_dibujado = 0;
            modos_dibujado[0] = !modos_dibujado[0];
            modos_dibujado[3] = false;
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
