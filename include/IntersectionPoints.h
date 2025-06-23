#ifndef INTERSECTIONPOINTS_H
#define INTERSECTIONPOINTS_H

#include <vector>
#include <utility>
#include "Point.h"
#include "LinearFunction.h"
#include "TangentialFunction.h"

class IntersectionPoints {
public:
    TangentialFunction tan_fun;   // Tangential function operand
    LinearFunction    lin_fun;    // Linear function operand

    // Construct with given tangential and linear functions
    IntersectionPoints(const TangentialFunction &tan_fun, const LinearFunction &lin_fun);

    // Compute `countPerDirection` intersection points per direction
    [[nodiscard]] std::vector<Point> GetIntersectionPoints(int countPerDirection) const;

private:
    const double accuracy = 1e-8;  // Tolerance for the root-finding algorithm

    // Evaluate f(x) = tan_fun(x) - lin_fun(x)
    [[nodiscard]] double f(double x) const;

    // Use bisection to find one intersection within `x_range`
    [[nodiscard]] Point GetIntersectionInRange(const std::pair<double, double> &x_range) const;
};

#endif // INTERSECTIONPOINTS_H
