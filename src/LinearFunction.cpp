//
// Created by artemiypank on 6/8/25.
//

#include "../include/LinearFunction.h"


double k, h;

LinearFunction::LinearFunction(double P_k, double P_h)
    : k(P_k), h(P_h) {}

double LinearFunction::func(double x) const {
    return k * x + h;
}

double LinearFunction::intersectionWithAxis_X() const {
    double x = -(h / k);
    return x;
}

double LinearFunction::intersectionWithAxis_Y() const {
    double y = h;
    return y;
}
