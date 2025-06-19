#include "../include/NumberConversion.h"
#include <cmath>


// алгоритм линейной интерполяции
double mapToRange(double raw, double A, double B, bool canBeZero, bool takeAbs) {
    double rez = raw * (B - A) + A;

    if (!canBeZero && rez == 0.0) rez = std::nextafter(0.0, 1.0);

    if (takeAbs) rez = std::fabs(rez);

    return rez;
}
