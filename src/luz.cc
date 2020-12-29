
#include "luz.h"
#include "aux.h"


Luz::Luz () {};

void Luz::activar(){
    if(glIsEnabled(id)){
        
        glLightfv(id,GL_DIFFUSE,colorDifuso);
        glLightfv(id,GL_SPECULAR,colorEspecular);
        glLightfv(id,GL_AMBIENT, colorAmbiente);

        glLightfv(id,GL_POSITION, posicion);
    }
}