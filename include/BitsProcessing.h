#ifndef BITSPROCESSING_H
#define BITSPROCESSING_H
#include <bitset>


template<std::size_t N>
void printBitset(const std::bitset<N> &bits) {
    for (size_t i = 0; i < N; ++i) {
        std::cout << bits[i];
        if ((i + 1) % 8 == 0) std::cout << ' ';
    }
    std::cout << std::endl;
}

inline void printBits_uint64_t(const uint64_t x) {
    const std::bitset<64> bs(x);
    printBitset(bs);
}

std::bitset<512> getBitset512FromString(const std::string &str);


double bitsetToDouble(const std::bitset<64>& bits);

std::array<double, 8> splitTo8Doubles(const std::bitset<512>& bits);

#endif //BITSPROCESSING_H
