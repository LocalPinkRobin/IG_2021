#include "monitor.h"

void Monitor::draw(int modo_dibujado, bool ajedrez){
    glPushMatrix();
        glTranslatef(0,47.5,-25);
        glRotatef(90,1.0, 0 ,0);
        glScalef(2,0.5,2);
        pantalla->draw(modo_dibujado,ajedrez);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0,10,6);
        glScalef(2,0.5,0.8);
        base->draw(modo_dibujado,ajedrez);
    glPopMatrix();
    
    glPushMatrix();
        glTranslatef(-35,20,10);
        glRotatef(rotaZ,0,0,1);
        glRotatef(rotaX,1,0,0);
        glScalef(0.75,0.75,0.75);
        joystick->draw(modo_dibujado,ajedrez);
    glPopMatrix();
    
}

void Monitor::modidicarJoystick (float inc){
    joystick->modificarExpansion(inc);
}

void Monitor::modificaRotacionX(float rotar){
    rotaX+=rotar;
    if(rotaX > TOPE){
        rotaX = TOPE;
    } else if ( rotaX < -TOPE){
        rotaX = -TOPE;
    }
}

void Monitor::modificaRotacionZ(float rotar){
    rotaZ+=rotar;
    if(rotaZ > TOPE){
        rotaZ = TOPE;
    } else if ( rotaZ < -TOPE){
        rotaZ = -TOPE;
    }
}