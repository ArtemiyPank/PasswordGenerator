//
// Created by artemiypank on 6/21/25.
//

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

using namespace CryptoPP;

static const std::string FILE_NAME = "HexDigitMap";


std::array<double, 8> GetParamsFromMasterKey(const std::string &master) {
    std::string digest = GetHash_HSA_512(master);

    std::bitset<512> bits;
    size_t pos = 0;
    for (const auto b: digest) {
        for (int i = 7; i >= 0; --i) {
            bits[pos] = (b >> i) & 1;
            pos++;
        }
    }


    if (DEBUG && !isInException(FILE_NAME)) {
        std::cout << "---------------------- Master key and hash ----------------------" << std::endl;

        std::cout << "Master key: " << master << std::endl;

        std::cout << "Hash in bits: ";

        printBitset(bits);

        std::cout << "====================== ====================== ======================" << std::endl;
    }

    return splitTo8Doubles(bits);
}


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

        std::cout << "---------------------- Parameters [0; 1) ----------------------" << std::endl;
        for (const double parameter: params) {
            std::cout << parameter << std::endl;
        }
        std::cout << "====================== ====================== ======================" << std::endl;

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
