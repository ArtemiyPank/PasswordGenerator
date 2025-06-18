#include <iomanip>
#include <iostream>

#include "../include/IntersectionPoints.h"
#include "../include/TangentialFunction.h"
#include "../include/LinearFunction.h"


int main() {
    const auto tan = TangentialFunction(0.5, 0.5, 0.5, 0.5, 0.5);
    const auto linear = LinearFunction(0.5, 0.5);


    const auto intersection = IntersectionPoints(tan, linear);

    const std::vector<Point> points = intersection.GetIntersectionPoints(4);

    std::cout << std::fixed << std::setprecision(20);

    for (Point point : points) {
        std::cout << "(" << point.x << "; " << point.y << ")" << std::endl;
    }
}



