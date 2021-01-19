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
#include "camara.h"


typedef enum {PRIMERA_PERSONA, EXAMINAR, DESACTIVADO} EstadosRaton;
typedef enum {NADA, SELOBJETO,SELVISUALIZACION,SELDIBUJADO, V_ALFA, V_BETA, ANIMACION, CAMARA} menu;
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
    void change_projection();
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
    const float MORE = 1.2;
    const float LESS = 0.8;
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

    int camara_actual;
    std::vector<Camara> camaras;

    EstadosRaton estadoRaton = DESACTIVADO;
	int xant = 0;
	int yant = 0;

    void seleccionaCamara(const int numeroCamara);


    public:

    Escena();
    void inicializar( int UI_window_width, int UI_window_height );
    void redimensionar( int newWidth, int newHeight ) ;
    void dibujarObjeto(GLenum modo);
    // Dibujar
    void dibujar() ;
    void dibujaSeleccion();

    // Interacción con la escena
    void clickRaton(int boton, int estado, int x, int i);
    void ratonMovido(int x, int y);
    bool teclaPulsada( unsigned char Tecla1, int x, int y ) ;
    void teclaEspecial( int Tecla1, int x, int y );
    void getClick (int x, int y);


    void animarModeloJerarquico();
};
#endif
