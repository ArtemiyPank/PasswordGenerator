#include <iomanip>
#include <iostream>

#include "NumberConversion.h"
#include "../include/IntersectionPoints.h"
#include "../include/TangentialFunction.h"
#include "../include/LinearFunction.h"
#include "../include/HashesProcessing.h"


int main() {

    const std::string master = "Master";

    const std::array<double, 8> parameters = GetParamsFromMasterKey(master);

    std::cout << "------------" << std::endl;

    for (double parameter: parameters) {
        std::cout << std::setprecision(10) << parameter << std::endl;
    }

    std::cout << "------------" << std::endl;



    const auto tan = TangentialFunction(parameters[0], parameters[1], parameters[2], parameters[3], parameters[4], parameters[5]);
    const auto linear = LinearFunction(parameters[6], parameters[7]);


    const auto intersection = IntersectionPoints(tan, linear);

    const std::vector<Point> points = intersection.GetIntersectionPoints(4);

    std::cout << std::fixed << std::setprecision(20);

    for (Point point : points) {
        std::cout << "(" << point.x << "; " << point.y << ")" << std::endl;
    }
}



