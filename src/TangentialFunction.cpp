#include <cmath>
#include <iostream>

#include "TangentialFunction.h"
#include "NumberConversion.h"
#include "Const.h"

static const std::string FILE_NAME = "TangentialFunction";

// Global parameters for the tangential function f(x) = g * ((c * tan(a * x + b) + d) / f)
double a, b, c, d, f, g;

void TangentialFunction::printTangentialParameters() const {
    std::cout << "---------------------- Tangential Function Parameters ----------------------" << std::endl;
    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl;
    std::cout << "c = " << c << std::endl;
    std::cout << "d = " << d << std::endl;
    std::cout << "f = " << f << std::endl;
    std::cout << "g = " << g << std::endl;
    std::cout << "====================== ====================== ======================" << std::endl;
}

TangentialFunction::TangentialFunction(double P_a, double P_b, double P_c, double P_d, double P_f,
                                       double P_g)
    : a(mapToRange(P_a, -10.0, 10.0)), // clamp P_a to [-10, 10] / {0}
      b(mapToRange(P_b, 0.0, M_PI, true)), // clamp P_b to [0, Pi]
      c(mapToRange(P_c, -10.0, 10.0)), // clamp P_c to [-10, 10] / {0}
      d(mapToRange(P_d, -5.0, 5.0)), // clamp P_d to [-5, 5] / {0}
      f(mapToRange(P_f, -10.0, 10.0)), // clamp P_f to [-10, 10] / {0}
      g(mapToRange(P_g, -10.0, 10.0)) // clamp P_g to [-10, 10] / {0}
{
    if (DEBUG && !isInException(FILE_NAME)) {
        printTangentialParameters();
    }
}

// f(x) = g * ((c * tan(a * x + b) + d) / f)
double TangentialFunction::func(const double x) const {
    return ((std::tan(a * x + b) * c + d) / f) * g;
}

//  x = ((π/2 + (n-1)*π) - b) / a
double TangentialFunction::GetAsymptoteByNumber(const int n) const {
    return ((M_PI / 2.0) + static_cast<double>(n - 1) * M_PI - b) / a;
}
