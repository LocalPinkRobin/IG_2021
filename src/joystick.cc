#include "joystick.h"

void Joystick::draw(int modo_dibujado, bool ajedrez){
    glPushMatrix();
        glTranslatef(0,30+(log(expansion)*10),0);
        glScalef(0.2,0.2,0.2);
        bola->draw(modo_dibujado,ajedrez);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0,10,0);
        glScalef(0.1,0.6*expansion,0.1);
        palanca->draw(modo_dibujado,ajedrez);
    glPopMatrix();
    
}
void Joystick::modificarExpansion(float inc){
    expansion +=inc;

    if (expansion > TOPE_SUPERIOR){
        expansion = TOPE_SUPERIOR;
    } else if (expansion < TOPE_INFERIOR){
        expansion = TOPE_INFERIOR;
    }
}