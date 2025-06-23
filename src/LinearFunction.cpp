#include <iostream>

#include "LinearFunction.h"
#include "Const.h"
#include "NumberConversion.h"

static const std::string FILE_NAME = "LinearFunction";

double k, h;

void LinearFunction::printLinearParameters() const {
    std::cout << "---------------------- Linear Function Parameters ----------------------" << std::endl;

    std::cout << "k = " << k << std::endl;
    std::cout << "h = " << h << std::endl;

    std::cout << "====================== ====================== ======================" << std::endl;
}

LinearFunction::LinearFunction(double P_k, double P_h)
    : k(mapToRange(P_k, -5, 5)),    // clamp P_k to [-5, 5] / {0}
      h(mapToRange(P_h, -100, 100, true))// clamp P_h to [-100, 100]
{
    if (DEBUG && !isInException(FILE_NAME)) {
        printLinearParameters();
    }
}

// y = kx + h
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
