#ifndef _ARCADE_H
#define _ARCADE_H

#include "cubo.h"
#include "cilindro.h"
#include "esfera.h"
#include "monitor.h"

class Arcade {

    private:

        Cubo *base = new Cubo (50);
        Monitor *superior = new Monitor ();

        float rotaY = 0;

    public:
        void draw(int modo_dibujado, bool ajedrez);
        void modificaRotacionY(float rotar);
        void modificarJoystick(float inc);
        void inclinarPalancaX(float rotar);
        void inclinarPalancaZ(float rotar);

        float getRotacionXJoystick(){return (superior->getRotacionX());};
        float getRotacionZJoystick(){return (superior->getRotacionZ());};
        float getTopeRotacionJoystick(){return (superior->getTope());};

        float getTopeSupExpansionJoystick() {return superior->getTopeSupExpansionJoystick();};
        float getTopeInfExpansionJoystick() {return superior->getTopeInfExpansionJoystick();};
        float getExpansionJoystick() { return superior->getExpansionJoystick();};
};


#endif