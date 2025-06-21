//
// Created by artemiypank on 6/21/25.
//

#include <array>
#include <iomanip>
#include <iostream>
#include <ostream>
#include <string>
#include <cryptopp/sha3.h>
#include <cryptopp/hex.h>
#include <cryptopp/filters.h>
#include <cryptopp/files.h>
#include <bitset>

#include "HexDigitMap.h"

#include "BitsProcessing.h"
#include "Const.h"
#include "HashesProcessing.h"
#include "IntersectionPoints.h"
#include "LinearFunction.h"
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


void GetRowNumbersForMap() {
    const std::string master = "Master";

    const std::array<double, 8> params = GetParamsFromMasterKey(master);

    if (DEBUG && !isInException(FILE_NAME)) {
        std::cout << "---------------------- Parameters (from 0 to 1) ----------------------" << std::endl;

        for (const double parameter: params) {
            std::cout << std::setprecision(10) << parameter << std::endl;
        }

        std::cout << "====================== ====================== ======================" << std::endl;
    }


    const auto tan = TangentialFunction(params[0], params[1], params[2], params[3], params[4], params[5]);
    const auto linear = LinearFunction(params[6], params[7]);

    const auto intersection = IntersectionPoints(tan, linear);

    const std::vector<Point> points = intersection.GetIntersectionPoints(4);


    if (DEBUG && !isInException(FILE_NAME)) {
        std::cout << "---------------------- Intersection points ----------------------" << std::endl;

        std::cout << std::fixed << std::setprecision(20);

        for (const Point point: points) {
            std::cout << "(" << point.x << "; " << point.y << ")" << std::endl;
        }

        std::cout << "====================== ====================== ======================" << std::endl;
    }
}

void GetHexDigitMap() {
    GetRowNumbersForMap();
}
