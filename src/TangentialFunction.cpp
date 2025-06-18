#include "../include/TangentialFunction.h"
#include <cmath>
#include "../include/Const.h"

double a, b, c, d, f;

TangentialFunction::TangentialFunction(double P_a, double P_b, double P_c, double P_d, double P_f)
    : a(P_a), b(P_b), c(P_c), d(P_d), f(P_f) {
}


double TangentialFunction::func(const double x) const {
    const double y = ((tan((a * x + b)) * c + d) / f);
    return y;
}

double TangentialFunction::GetAsymptoteByNumber(const int n) const {
    const double x = ((Pi / 2.0) + static_cast<double>(n - 1) * Pi - b) / a;

    return x;
}

