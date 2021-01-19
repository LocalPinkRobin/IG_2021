#include "aux.h"

bool comparaFloats(float a, float b, float epsilon){
    return abs(a-b)<epsilon;
}
bool operator == (const Tupla3f & t1, const Tupla3f & t2){
	return (comparaFloats(t1(0), t2(0)) && comparaFloats(t1(1), t2(1)) && comparaFloats(t1(2), t2(2)) );
}