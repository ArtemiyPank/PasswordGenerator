#include "../include/TangentialFunction.h"
#include <cmath>
#include <cstdint>
#include <iostream>
#include <ostream>

#include "NumberConversion.h"
#include "../include/Const.h"

using namespace std;


double a, b, c, d, f, g;

// double trim(double value, double mod, bool canBeZero = false, bool take_abs = false) {
//     cout << "v start = " << value << endl;
//
//     double v = std::fmod(value, mod);
//     if (take_abs) v = std::fabs(v);
//     if (!canBeZero && v == 0.0) v = 1e-6;
//
//     static constexpr double scale = 1e10;
//     v = std::round(v * scale) / scale;
//
//     cout << "v end = " << v << endl;
//
//
//     return v;
// }


void TangentialFunction::printTangentialParameters() const {
    cout << "========= Tangential Function Parameters" << endl;

    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "c = " << c << endl;
    cout << "d = " << d << endl;
    cout << "f = " << f << endl;
    cout << "g = " << g << endl;

    cout << "========= -------------------------------" << endl;
}


TangentialFunction::TangentialFunction(double P_a, double P_b, double P_c, double P_d, double P_f,
                                       double P_g) : a(mapToRange(P_a, -10.0, 10.0)),
                                                     b(mapToRange(P_b, 0, Pi, true)),
                                                     c(mapToRange(P_c, -10.0, 10.0)),
                                                     d(mapToRange(P_d, -5.0, 5.0)),
                                                     f(mapToRange(P_f, -10.0, 10.0)),
                                                     g(mapToRange(P_g, -10.0, 10.0)) {

    printTangentialParameters();
}


double TangentialFunction::func(const double x) const {
    const double y = ((tan((a * x + b)) * c + d) / f) * g;
    return y;
}

double TangentialFunction::GetAsymptoteByNumber(const int n) const {
    const double x = ((Pi / 2.0) + static_cast<double>(n - 1) * Pi - b) / a;

    return x;
}
