#ifndef INTERSECTIONPOINTS_H
#define INTERSECTIONPOINTS_H

#include <string>
#include <vector>
#include <utility>
#include "Point.h"

#include "LinearFunction.h"
#include "TangentialFunction.h"



class IntersectionPoints {
public:
    TangentialFunction tan_fun;
    LinearFunction    lin_fun;

    IntersectionPoints(const TangentialFunction &tan_fun, const LinearFunction &lin_fun);

    [[nodiscard]] std::vector<Point> GetIntersectionPoints(int countPerDirection) const;

private:
    // Точность поиска
    const double accuracy = 1e-14;

    // F(x) = tan_fun(x) - lin_fun(x)
    [[nodiscard]] double f(double x) const;

    [[nodiscard]] Point GetIntersectionInRange(const std::pair<double, double> &x_range) const;
};

#endif // INTERSECTIONPOINTS_H
