#include "../include/IntersectionPoints.h"

#include <iostream>

IntersectionPoints::IntersectionPoints(
    const TangentialFunction &P_tan_fun,
    const LinearFunction &P_lin_fun
) : tan_fun(P_tan_fun), lin_fun(P_lin_fun) {
}

// Разность функций f(x) = tan_fun(x) - lin_fun(x)
double IntersectionPoints::f(double x) const {
    return tan_fun.func(x) - lin_fun.func(x);
}

// Поиск всех точек пересечения на заданном числе подотрезков
std::vector<Point> IntersectionPoints::GetIntersectionPoints(const int countPerDirection) const {
    if (countPerDirection <= 0) return {};

    std::vector<Point> points;
    points.reserve(countPerDirection);

    // Начальные границы: от 1 до 2-ой асимптоты
    std::pair<double, double> bounds = {tan_fun.GetAsymptoteByNumber(1), tan_fun.GetAsymptoteByNumber(2)};

    for (int i = 2; i <= countPerDirection + 1; ++i) {
        Point intersection = GetIntersectionInRange(bounds);
        points.push_back(intersection);

        // Сдвигаем границы
        bounds.first = bounds.second;
        bounds.second = tan_fun.GetAsymptoteByNumber(i + 1);

        std::cout << "bounds: " << bounds.first << " | " << bounds.second << std::endl;
    }

    return points;
}

// Метод бисекции для поиска одной точки пересечения на заданном промежутке
Point IntersectionPoints::GetIntersectionInRange(const std::pair<double, double> &x_range) const {
    double x_min = x_range.first + accuracy;
    double x_max = x_range.second - accuracy;

    if (f(x_min) * f(x_max) > 0) {
        throw std::runtime_error("Function does not change sign on interval");
    }

    const int repetitions = fabs(static_cast<int>(std::log2((x_max - x_min) / accuracy)) + 1);
    double c = 0.0;

    for (int i = 0; i < repetitions; ++i) {
        c = (x_min + x_max) / 2.0;
        const double value = f(c);

        if (std::abs(value) < accuracy) {
            return {c, tan_fun.func(c)};
        }

        if (value > 0.0) {
            x_max = c;
        } else {
            x_min = c;
        }
    }

    // Финальное приближение
    c = (x_min + x_max) / 2.0;

    return {c, tan_fun.func(c)};
}
