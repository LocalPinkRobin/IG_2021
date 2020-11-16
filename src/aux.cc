#include "aux.h"

bool comparaFloats(float a, float b, float epsilon){
    return abs(a-b)<epsilon;
}