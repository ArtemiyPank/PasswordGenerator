#include <array>
#include <iomanip>
#include <iostream>
#include <ostream>
#include <string>
#include <cryptopp/sha3.h>
#include <cryptopp/files.h>
#include <bitset>
#include <map>

#include "HexDigitMap.h"
#include "BitsProcessing.h"
#include "Const.h"
#include "HashesProcessing.h"
#include "IntersectionPoints.h"
#include "LinearFunction.h"
#include "NumberConversion.h"
#include "TangentialFunction.h"

static const std::string FILE_NAME = "HexDigitMap";


// Derive eight uniform parameters in [0,1) from the master key
std::array<double, 8> GetParamsFromMasterKey(const std::string &master) {
    const std::bitset<512> bits = GetHash_HSA_512(master);

    if (DEBUG && !isInException(FILE_NAME)) {
        std::cout << "---------------------- Master key and hash ----------------------\n"
                  << "Master key: " << master << "\n"
                  << "Hash in bits: ";
        printBitset(bits);
        std::cout << "====================== ====================== ======================" << std::endl;
    }

    return splitTo8Doubles(bits);
}


// Generate 16 row indices by intersecting a tangent-based and linear function
std::array<int, 16> GetRowNumbersForMap(const std::string &master) {
    const std::array<double, 8> params = GetParamsFromMasterKey(master);

    const auto tan = TangentialFunction(params[0], params[1], params[2], params[3], params[4], params[5]);
    const auto linear = LinearFunction(params[6], params[7]);

    const auto intersection = IntersectionPoints(tan, linear);

    const std::vector<Point> points = intersection.GetIntersectionPoints(16);


    std::array<int, 16> rowNumbersForMap{};
    for (std::size_t i = 0; i < 8; ++i) {
        rowNumbersForMap[i * 2] = extractFractionDigits(points[i].x, 3, NumberOfDigitsInHexDigitMap);
        rowNumbersForMap[i * 2 + 1] = extractFractionDigits(points[i].y, 3, NumberOfDigitsInHexDigitMap);
    }

    if (DEBUG && !isInException(FILE_NAME)) {
        std::cout << std::fixed << std::setprecision(20);

        std::cout << "---------------------- Intersection points ----------------------" << std::endl;
        for (const Point point: points) {
            std::cout << "(" << point.x << "; " << point.y << ")" << std::endl;
        }
        std::cout << "====================== ====================== ======================" << std::endl;

        std::cout << "---------------------- Row numbers for map ----------------------" << std::endl;
        for (const int num: rowNumbersForMap) {
            std::cout << num << std::endl;
        }
        std::cout << "====================== ====================== ======================" << std::endl;
    }

    return rowNumbersForMap;
}


// Build a mapping from hex digit to its corresponding row number
std::map<char, int> GetHexDigitMap(const std::string &master) {
    std::array<int, 16> rowNumbersForMap = GetRowNumbersForMap(master);

    std::array<char, 16> hexSymbols{'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

    std::map<char, int> hexDigitMap;

    for (std::size_t i = 0; i < 16; ++i) {
        hexDigitMap[hexSymbols[i]] = rowNumbersForMap[i];
    }

    if (DEBUG && !isInException(FILE_NAME)) {
        std::cout << "---------------------- Hex digit map ----------------------" << std::endl;
        for (const auto [key, value]: hexDigitMap) {
            std::cout << key << " -> " << value << std::endl;
        }
        std::cout << "====================== ====================== ======================" << std::endl;
    }


    return hexDigitMap;
}
