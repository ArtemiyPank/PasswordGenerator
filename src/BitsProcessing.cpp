#include <array>
#include <bitset>
#include <cstdint>
#include <cstring>
#include <iomanip>
#include <iostream>

#include "BitsProcessing.h"

#include "Const.h"

static const std::string FILE_NAME = "BitsProcessing";



double bitsetToDouble(const std::bitset<64> &bits) {
    const uint64_t uint64 = bits.to_ullong();

    double doubleValue;

    std::memcpy(&doubleValue, &uint64, sizeof(double));

    return doubleValue;
}


double bitsToUniform01(const uint64_t bitNum) {
    // младшие 52 бита — мантисса
    const uint64_t mantissa = bitNum & ((1ULL << 52) - 1);
    // экспонента = bias (1023) => истинная степень = 0
    const uint64_t bits = (static_cast<uint64_t>(1023) << 52) | mantissa;
    const auto d = std::bit_cast<double>(bits);
    return d - 1.0;  // [0,1)
}

std::array<double, 8> splitTo8Doubles(const std::bitset<512> &bits) {
    std::array<double, 8> result{};

    if (DEBUG && !isInException(FILE_NAME))
            std::cout << "---------------------- Part of hash in bits and double ----------------------" << std::endl;

    for (size_t chunk = 0; chunk < 8; chunk++) {
        const size_t base = chunk * 64;
        std::bitset<64> numBits;
        for (size_t i = 0; i < 64; ++i) {
            numBits[i] = bits[base + i];
        }

        const double numDouble = bitsToUniform01(numBits.to_ulong());

        result[chunk] = numDouble;


        if (DEBUG && !isInException(FILE_NAME)) {

            std::cout << "chunk - " << chunk << std::endl << "bitset - ";
            printBitset(numBits);
            std::cout << std::fixed << std::setprecision(20);
            std::cout << "double - " << numDouble << std::endl;
            std::cout << "----------------------" << std::endl;

        }
    }

    if (DEBUG && !isInException(FILE_NAME))
        std::cout << "====================== ====================== ======================" << std::endl;



    return result;
}