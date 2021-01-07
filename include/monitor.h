#ifndef _MONITOR_H
#define _MONITOR_H

#include "cubo.h"
#include "joystick.h"

class Monitor{
    
    private:

        const float TOPE = 45;
        
        Cubo *pantalla = new Cubo(50);
        Cubo *base = new Cubo (50);
        Joystick *joystick = new Joystick ();

        float rotaX = 0;
        float rotaZ = 0;
        
    public:
        void draw(int modo_dibujado, bool ajedrez);

        void modificaRotacionX(float rotar);
        void modificaRotacionZ(float rotar);
        void modidicarJoystick(float inc);

        float getRotacionX(){return rotaX;};
        float getRotacionZ(){return rotaZ;};
        float getTope(){return TOPE;};

        float getTopeSupExpansionJoystick() {return joystick->getTopeSupExpansionJoystick();};
        float getTopeInfExpansionJoystick() {return joystick->getTopeInfExpansionJoystick();};
        float getExpansionJoystick() {return joystick->getExpansionJoystick();};


};

#endif