#include <cmath>

#include "NumberConversion.h"


static const std::string FILE_NAME = "NumberConversion";

// алгоритм линейной интерполяции
double mapToRange(double raw, double A, double B, bool canBeZero, bool takeAbs) {
    double rez = raw * (B - A) + A;

    if (!canBeZero && rez == 0.0) rez = std::nextafter(0.0, 1.0);

    if (takeAbs) rez = std::fabs(rez);

    return rez;
}

// Извлечение последовательности цифр из дробной части числа `n`
int extractFractionDigits(double n, int startPosition, int length) {
    // отбрасываем всё до startPosition и сдвигаем к нулю
    n = fmod(std::fabs(n), std::pow(10, -(startPosition - 1))) * pow(10, (startPosition - 1));

    // оставляем столько цифр, сколько нужно
    n = floor(n * std::pow(10, length));

    return static_cast<int>(n);
}
