#include "camara.h"

Camara::Camara(const Tupla3f & eye, const Tupla3f &  at, const Tupla3f &  up, 
               const int & tipo, const float & near, const float & far){

    this->eye = eye;
    this->at = at;
    this->up = up;

    this->tipo = tipo;

    this->near = near;
    this->far = far;

    seleccion = NINGUNO;
}

void Camara::setObserver(){
    gluLookAt(eye(0), eye(1), eye(2),
              at(0), at(1), at(2),
              up(0), up(1), up(2) );
}

void Camara::setProyeccion(){
    if (tipo == 0){
        glOrtho( left, right, bottom, top, near, far );
    } else {
        glFrustum( left, right, bottom, top, near, far );
    }
}
void Camara::setSeleccion(objetos a){
    seleccion = a;
}
objetos Camara::getSeleccion() {
    return seleccion;
}

void Camara::setUp(const Tupla3f & Up){
	up = Up;
}

void Camara::setAt(const Tupla3f & At){
	at = At;
}

void Camara::setEye(const Tupla3f & Eye){
	eye = Eye;
}

void Camara::setLeft(const float & Left){
	left = Left;
}

void Camara::setRight(const float & Right){
	right = Right;
}


void Camara::setNear(const float & Near){
	near = Near;
}
void Camara::setFar(const float & Far){
	far = Far;
}

void Camara::setTop(const float & Top){
	top = Top;
}

void Camara::setBottom(const float & Bottom){
	bottom = Bottom;
}
float Camara::getNear() const {
	return near;
}

float Camara::getFar() const {
	return far;
}

float Camara::getLeft() const {
	return left;
}

float Camara::getRight() const {
	return right;
}

Tupla3f Camara::getEye() const{
	return eye;
}

Tupla3f Camara::getAt() const {
	return at;
}

Tupla3f Camara::getUp() const {
	return up;
}
float Camara::getTop() const {
	return top;
}
float Camara::getBottom() const {
	return bottom;
}

//void Camara::setObjetoSeleccionado(){}

void Camara::rotarXExaminar(const float angulo){

    //Coloco el eye en el centro para que no afecte a la rotación
    Tupla3f eye_centro = eye - at;

    //Aplico la rotación
    float modulo = sqrt(eye_centro.lengthSq());

    eye_centro[1] = cos(angulo) * eye_centro[1] - sin(angulo) * eye_centro[2];
    eye_centro[2] = sin(angulo) * eye_centro[1] + cos(angulo) * eye_centro[2];

    //Lo normalizo y lo multiplico por el modulo para que tenga la misma escala
    eye_centro =eye_centro.normalized() * modulo;

    //Dejo el punto donde estaba :)
    eye = eye_centro + at;
}

void Camara::rotarYExaminar(const float angulo){

    //Coloco el eye en el centro para que no afecte a la rotación
    Tupla3f eye_centro = eye - at;

    //Aplico la rotación
    float modulo = sqrt(eye_centro.lengthSq());

    eye_centro[0] = cos(angulo) * eye_centro[0] + sin(angulo) * eye_centro[2];
    eye_centro[2] = -sin(angulo) * eye_centro[0] + cos(angulo) * eye_centro[2];

    //Lo normalizo y lo multiplico por el modulo para que tenga la misma escala
    eye_centro =eye_centro.normalized() * modulo;

    //Dejo el punto donde estaba :)
    eye = eye_centro + at;
}

void Camara::rotarZExaminar(const float angulo){

    //Coloco el eye en el centro para que no afecte a la rotación
    Tupla3f eye_centro = eye - at;

    //Aplico la rotación
    float modulo = sqrt(eye_centro.lengthSq());

    eye_centro[0] = cos(angulo)*eye_centro[0] - sin(angulo) * eye_centro[1];
    eye_centro[1] = sin(angulo) * eye_centro[0] + cos(angulo) * eye_centro[1];

    //Lo normalizo y lo multiplico por el modulo para que tenga la misma escala
    eye_centro =eye_centro.normalized() * modulo;

    //Dejo el punto donde estaba :)
    eye = eye_centro + at;
}

void Camara::rotarXFirstPerson(const float angulo){
    
    //Ponemos e at en el centro
    Tupla3f at_centro = at - eye;

    //Aplico la rotacion
	float modulo = sqrt(at_centro.lengthSq());    
    
	at_centro[1] = cos(angulo)*at_centro[1] - sin(angulo) * at_centro[2];
    at_centro[2] = sin(angulo) * at_centro[1] + cos(angulo) * at_centro[2];

    //Lo normalizo y lo multiplico por el modulo para que tenga la misma escala
    at_centro = at_centro.normalized() * modulo;

    //Lo vuelvo a dejar en su sitio
    at = at_centro + eye;
}

void Camara::rotarYFirstPerson(const float angulo){
    
    //Ponemos e at en el centro
    Tupla3f at_centro = at - eye;

    //Aplico la rotacion
	float modulo = sqrt(at_centro.lengthSq());    
    
	
	at_centro(0) = cos(angulo)*at_centro(0) + sin(angulo) * at_centro(2);
    at_centro(2) = -sin(angulo) * at_centro(0) + cos(angulo) * at_centro(2);
    
    //Lo normalizo y lo multiplico por el modulo para que tenga la misma escala
    at_centro = at_centro.normalized() * modulo;

    //Lo vuelvo a dejar en su sitio
    at = at_centro + eye;
}

void Camara::rotarZFirstPerson(const float angulo){
    
    //Ponemos e at en el centro
    Tupla3f at_centro = at - eye;

    //Aplico la rotacion
	float modulo = sqrt(at_centro.lengthSq());    
    
    at_centro(0) = cos(angulo)*at_centro(0) - sin(angulo) * at_centro(1);
    at_centro(1) = sin(angulo) * at_centro(0) + cos(angulo) * at_centro(1);

    //Lo normalizo y lo multiplico por el modulo para que tenga la misma escala
    at_centro = at_centro.normalized() * modulo;

    //Lo vuelvo a dejar en su sitio
    at = at_centro + eye;
}

void Camara::girar(int x, int y){
    Tupla3f at_centro = at - eye;

    if(at_centro[2] > 0){
        y = -y;
    }
    rotarXFirstPerson(-y * SEXA_TO_RAD);
	rotarYFirstPerson(-x * SEXA_TO_RAD);


}
void Camara::girarEx(int x, int y){
    rotarXExaminar(y * SEXA_TO_RAD);
	rotarYExaminar(x * SEXA_TO_RAD);
}

void Camara::zoom(const float factor){
    left *=factor;
    top *=factor;
    bottom *=factor;
    right *=factor;

}
void Camara::mover(float x, float y, float z){

}
