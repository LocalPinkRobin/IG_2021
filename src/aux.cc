#include "aux.h"

bool comparaFloats(float a, float b, float epsilon = 0.00005f){
    return abs(a-b)<epsilon;
}