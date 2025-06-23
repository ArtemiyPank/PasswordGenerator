#ifndef BITSPROCESSING_H
#define BITSPROCESSING_H

#include <bitset>
#include <array>
#include <cstdint>
#include <string>
#include <iostream>


// Print each bit of a bitset, grouping bits in bytes for readability
template<std::size_t N>
void printBitset(const std::bitset<N> &bits) {
    for (size_t i = 0; i < N; ++i) {
        std::cout << bits[i];
        if ((i + 1) % 8 == 0) std::cout << ' ';
    }
    std::cout << std::endl;
}

// Print the binary form of a 64-bit unsigned integer
inline void printBitsUInt64(uint64_t x) {
    printBitset(std::bitset<64>(x));
}

// Build a 512-bit bitset from a raw byte string (8 bits per character)
std::bitset<512> getBitset512FromString(const std::string &str);

// Reinterpret a 64-bit bitset as an IEEE-754 double
double bitsetToDouble(const std::bitset<64> &bits);

// Split a 512-bit bitset into eight 64-bit chunks and map each to a uniform [0,1) double
std::array<double, 8> splitTo8Doubles(const std::bitset<512> &bits);

#endif // BITSPROCESSING_H
