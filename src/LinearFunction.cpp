//
// Created by artemiypank on 6/8/25.
//

#include "../include/LinearFunction.h"

#include <iostream>

#include "NumberConversion.h"

using namespace std;

double k, h;

void LinearFunction::printLinearParameters() const {
    cout << "========= Linear Function Parameters" << endl;

    cout << "k = " << k << endl;
    cout << "h = " << h << endl;

    cout << "========= -------------------------------" << endl;
}
LinearFunction::LinearFunction(double P_k, double P_h)
    : k(mapToRange(P_k, -5, 5)),
      h(mapToRange(P_h, -15, 15, true)) {

    printLinearParameters();
}

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
