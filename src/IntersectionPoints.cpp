#include <cmath>
#include <iostream>

#include "IntersectionPoints.h"
#include "Const.h"

static const std::string FILE_NAME = "IntersectionPoints";

IntersectionPoints::IntersectionPoints(
    const TangentialFunction &P_tan_fun,
    const LinearFunction &P_lin_fun
) : tan_fun(P_tan_fun), lin_fun(P_lin_fun) {
}

// Compute difference between tangential and linear functions at x
double IntersectionPoints::f(double x) const {
    return tan_fun.func(x) - lin_fun.func(x);
}

// Find intersection points over a specified number of intervals
std::vector<Point> IntersectionPoints::GetIntersectionPoints(const int countPerDirection) const {
    if (countPerDirection <= 0) return {};

    std::vector<Point> points;
    points.reserve(countPerDirection);

    // Initial interval between the 1st and 2nd asymptotes
    std::pair<double, double> bounds = {
        tan_fun.GetAsymptoteByNumber(1),
        tan_fun.GetAsymptoteByNumber(2)
    };

    if (DEBUG && !isInException(FILE_NAME))
        std::cout << "---------------------- Intersection boundaries ----------------------" << std::endl;

    for (int i = 2; i <= countPerDirection + 1; ++i) {
        Point intersection = GetIntersectionInRange(bounds);
        points.push_back(intersection);

        // Shift interval boundaries to the next asymptotes
        bounds.first = bounds.second;
        bounds.second = tan_fun.GetAsymptoteByNumber(i + 1);

        if (DEBUG && !isInException(FILE_NAME)) {
            std::cout << "Bounds " << (i - 1) << ": "
                    << bounds.first << " | " << bounds.second << "\n";
        }
    }

    if (DEBUG && !isInException(FILE_NAME))
        std::cout << "====================== ====================== ======================" << std::endl;

    return points;
}

// Bisection method to find one intersection within the given range
Point IntersectionPoints::GetIntersectionInRange(const std::pair<double, double> &x_range) const {
    double x_min = x_range.first + accuracy;
    double x_max = x_range.second - accuracy;

    if (f(x_min) * f(x_max) > 0) {
        throw std::runtime_error("Function does not change sign on interval");
    }

    const int repetitions = std::abs(static_cast<int>(std::log2((x_max - x_min) / accuracy))) + 1;
    double c = 0.0;

    for (int i = 0; i < repetitions; ++i) {
        c = 0.5 * (x_min + x_max);
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

    // Final approximation
    c = 0.5 * (x_min + x_max);
    return {c, tan_fun.func(c)};
}
