#include "arcade.h"

void Arcade::draw(int modo_dibujado, bool ajedrez){
    glPushMatrix();
        glTranslatef(0,-65,-6.25);
        glScalef(2, 2.5, 1.25);
        base->draw(modo_dibujado,ajedrez);
    glPopMatrix();

    glPushMatrix();
        glRotatef(rotaY,0,1,0);
        superior->draw(modo_dibujado,ajedrez);
    glPopMatrix();
    
}
        
void Arcade::modificaRotacionY(float rotar){
    rotaY+=rotar;
    rotaY=fmod(rotaY,360);
}

void Arcade::modificarJoystick(float inc){
    superior->modidicarJoystick(inc);
}

void Arcade::inclinarPalancaX(float rotar){
    superior->modificaRotacionX(rotar);
}

void Arcade::inclinarPalancaZ(float rotar){
    superior->modificaRotacionZ(rotar);
}
