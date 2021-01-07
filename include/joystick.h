#ifndef _JOYSTICK_H
#define _JOYSTICK_H

#include "esfera.h"
#include "cilindro.h"

class Joystick{
    
    private:
        const float TOPE_SUPERIOR = 2.5;
        const float TOPE_INFERIOR = 0.5;

        Esfera *bola = new Esfera(50,50,50,true,true);
        Cilindro *palanca = new Cilindro(50,50,50,true,true);
        float expansion = 1.0;


    public:
        void draw(int modo_dibujado, bool ajedrez);
        void modificarExpansion(float inc);

        float getTopeSupExpansionJoystick() {return TOPE_SUPERIOR;};
        float getTopeInfExpansionJoystick() {return TOPE_INFERIOR;};
        float getExpansionJoystick() {return expansion;};


};

#endif