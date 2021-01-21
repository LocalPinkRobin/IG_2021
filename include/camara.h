#ifndef CAMARA_H_INCLUDED
#define CAMARA_H_INCLUDED

#include "aux.h"

typedef enum {CUBO, TETRAEDRO, CONO, ESFERA, OBJPLY, REVO, REVO_2, ARCADE, ARCADE2,CILINDRO, NINGUNO} objetos;


class Camara {

    private:
        Tupla3f eye;
        Tupla3f at;
        Tupla3f up;

        int tipo; // 0.ORTOGONAL o 1.PERSPECTIVA
        float left, right, top, bottom, near,far;

        objetos seleccion;

    public:
        Camara (const Tupla3f & eye, const Tupla3f &  at, const Tupla3f &  up,
                const int & tipo, const float & near, const float & far);
        
        void rotarXExaminar (const float angulo);
        void rotarYExaminar (const float angulo);
        void rotarZExaminar (const float angle);

        void rotarXFirstPerson (const float angulo);
        void rotarYFirstPerson (const float angulo);
        void rotarZFirstPerson (const float angulo);

        void setObserver();
        void setProyeccion ();

       // void getObjetoSeleccionado();
        // void setObjetoSeleccionado();

        Tupla3f getEye() const;
        Tupla3f getAt() const ;
        Tupla3f getUp() const;

        float getLeft()const;
        float getRight()const;
        float getNear()const;
        float getFar()const;
        float getTop()const;
        float getBottom()const;
        objetos getSeleccion();
        void setSeleccion(objetos a);


        void setEye(const Tupla3f & Eye);
        void setAt(const Tupla3f & At);
        void setUp(const Tupla3f & Up);

        void setLeft(const float & Left);
        void setRight(const float & Right);
        void setNear(const float & Near);
        void setFar(const float & Far);
        void setTop(const float & Top);
        void setBottom(const float & Bottom);

        void girar(int x, int y);
        void girarEx(int x, int y);


        void mover(float x, float y, float z);
        void zoom (float factor);

};

#endif