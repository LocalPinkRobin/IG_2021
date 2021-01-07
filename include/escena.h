#ifndef _ESCENA_H
#define _ESCENA_H

#include "ejes.h"
#include "malla.h"
#include "cubo.h"
#include "tetraedro.h"
#include "objply.h"
#include "objrevolucion.h"
#include "cilindro.h"
#include "cono.h"
#include "esfera.h"
#include "luz_direccional.h"
#include "luz_posicional.h"
#include "arcade.h"



typedef enum {NADA, SELOBJETO,SELVISUALIZACION,SELDIBUJADO, V_ALFA, V_BETA} menu;
class Escena
{

    private:



    // ** PARÁMETROS DE LA CÁMARA (PROVISIONAL)
        
        // variables que definen la posicion de la camara en coordenadas polares
    GLfloat Observer_distance;
    GLfloat Observer_angle_x;
    GLfloat Observer_angle_y;

    // variables que controlan la ventana y la transformacion de perspectiva
    GLfloat Width, Height, Front_plane, Back_plane;

    // Transformación de cámara
    void change_projection( const float ratio_xy );
    void change_observer();


    void clear_window();

    int modo_dibujado;

    menu modoMenu=NADA;
    // Objetos de la escena
    Ejes ejes;
    Cubo * cubo = nullptr ; // es importante inicializarlo a 'nullptr'
    Tetraedro * tetraedro= nullptr ; // es importante inicializarlo a 'nullptr'
    ObjPLY * objetoply = nullptr;
    ObjRevolucion * peon_blanco = nullptr;
    ObjRevolucion * peon_negro = nullptr;

    bool animacionAutomatica = false;

    Arcade * arcade = nullptr;
    float incrementoRotaXJoystick = 5;
    float incrementoRotaZJoystick = 2;
    float rotacionPantalla = 2;
    float incrementoJoystick = 0.1;


    Cilindro * cilindro = nullptr;
    Cono * cono = nullptr;
    Esfera * bola = nullptr;

    LuzPosicional * posicional = nullptr;
    LuzDireccional * direccional = nullptr;

    GLenum sombreado = GL_SMOOTH;


    std::vector<bool> visibilidad_objetos;
    std::vector<bool> visualizacion_dibujado;






    public:

    Escena();
    void inicializar( int UI_window_width, int UI_window_height );
    void redimensionar( int newWidth, int newHeight ) ;
    void dibujarObjeto(GLenum modo);
    // Dibujar
    void dibujar() ;

    // Interacción con la escena
    bool teclaPulsada( unsigned char Tecla1, int x, int y ) ;
    void teclaEspecial( int Tecla1, int x, int y );

    void animarModeloJerarquico();
};
#endif
