#include <array>
#include <bitset>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <iomanip>

#include "BitsProcessing.h"
#include "Const.h"

static const std::string FILE_NAME = "BitsProcessing";

// Interpret each byte of `str` as 8 bits, in big-endian order, and pack into a 512-bit bitset
std::bitset<512> getBitset512FromString(const std::string &str) {
    std::bitset<512> bits;
    size_t pos = 0;
    for (const auto b: str) {
        for (int i = 7; i >= 0; --i) {
            bits[pos++] = (b >> i) & 1;
        }
    }
    return bits;
}

// Reinterpret a 64-bit bitset as a IEEE-754 double
double bitsetToDouble(const std::bitset<64> &bits) {
    const uint64_t uint64 = bits.to_ullong();

    double doubleValue;
    std::memcpy(&doubleValue, &uint64, sizeof(double));

    return doubleValue;
}

// Convert a 64-bit integer to a double in [0,1) by treating low 52 bits as mantissa, exponent = 0
double bitsToUniform01(const uint64_t bitNum) {
    // the lower 52 bits are the mantissa
    const uint64_t mantissa = bitNum & ((1ULL << 52) - 1);

    // exponent = bias (1023)
    const uint64_t bits = (static_cast<uint64_t>(1023) << 52) | mantissa;
    const auto d = std::bit_cast<double>(bits);

    return d - 1.0;  // [0,1)
}

// Split a 512-bit bitset into eight 64-bit chunks, convert each to a uniform double in [0,1)
std::array<double, 8> splitTo8Doubles(const std::bitset<512> &bits) {
    std::array<double, 8> result{};

    if (DEBUG && !isInException(FILE_NAME))
            std::cout << "---------------------- Part of hash in bits and double ----------------------" << std::endl;

    for (size_t chunk = 0; chunk < 8; chunk++) {
        const size_t base = chunk * 64;
        // extract 64 bits from the bitset
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