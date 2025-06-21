#include <cmath>
#include <iostream>
#include <ostream>

#include "TangentialFunction.h"
#include "NumberConversion.h"
#include "Const.h"

static const std::string FILE_NAME = "TangentialFunction";


using namespace std;


double a, b, c, d, f, g;


void TangentialFunction::printTangentialParameters() const {
    std::cout << "---------------------- Tangential Function Parameters ----------------------" << std::endl;

    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "c = " << c << endl;
    cout << "d = " << d << endl;
    cout << "f = " << f << endl;
    cout << "g = " << g << endl;

    std::cout << "====================== ====================== ======================" << std::endl;
}


TangentialFunction::TangentialFunction(double P_a, double P_b, double P_c, double P_d, double P_f,
                                       double P_g) : a(mapToRange(P_a, -10.0, 10.0)),
                                                     b(mapToRange(P_b, 0, Pi, true)),
                                                     c(mapToRange(P_c, -10.0, 10.0)),
                                                     d(mapToRange(P_d, -5.0, 5.0)),
                                                     f(mapToRange(P_f, -10.0, 10.0)),
                                                     g(mapToRange(P_g, -10.0, 10.0)) {
    if (DEBUG && !isInException(FILE_NAME)) {
        printTangentialParameters();
    }
}


double TangentialFunction::func(const double x) const {
    const double y = ((tan((a * x + b)) * c + d) / f) * g;
    return y;
}

double TangentialFunction::GetAsymptoteByNumber(const int n) const {
    const double x = ((Pi / 2.0) + static_cast<double>(n - 1) * Pi - b) / a;

    return x;
}
