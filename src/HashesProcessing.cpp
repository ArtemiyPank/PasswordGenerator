#include <cryptopp/sha3.h>
#include <cryptopp/hex.h>
#include <cryptopp/filters.h>
#include <cryptopp/files.h>
#include <iostream>
#include <string>
#include <bitset>
#include <iomanip>

template<std::size_t N>
void printBitset(const std::bitset<N> &bits) {
    for (size_t i = 0; i < N; ++i) {
        std::cout << bits[i];
        if ((i + 1) % 8 == 0) std::cout << ' ';
    }
    std::cout << std::endl;
}

void printBits_uint64_t(const uint64_t x) {
    const std::bitset<64> bs(x);
    printBitset(bs);
}

// double bitsetToDouble(const std::bitset<64> &bits) {
//     const uint64_t uint64 = bits.to_ullong();
//
//     double doubleValue;
//
//     std::memcpy(&doubleValue, &uint64, sizeof(double));
//
//     return doubleValue;
// }


double bitsToUniform01(uint64_t bitNum) {
    // младшие 52 бита — мантисса
    uint64_t mant = bitNum & ((1ULL << 52) - 1);
    // экспонента = bias (1023) → истинная степень = 0
    uint64_t bits = (uint64_t(1023) << 52) | mant;
    double d = std::bit_cast<double>(bits);
    return d - 1.0;  // теперь [0,1)
}



std::array<double, 8> splitTo8Doubles(const std::bitset<512> &bits) {
    std::array<double, 8> result{};

    for (size_t chunk = 0; chunk < 8; chunk++) {
        const size_t base = chunk * 64;
        // uint64_t numBits = 0;
        std::bitset<64> numBits;
        for (size_t i = 0; i < 64; ++i) {
            numBits[i] = bits[base + i];
        }

        const double numDouble = bitsToUniform01(numBits.to_ulong());

        std::cout << "chunk - " << chunk << std::endl << "bitset - 2";
        printBitset(numBits);
        std::cout << std::fixed << std::setprecision(20);
        std::cout << "double - " << numDouble << std::endl;
        std::cout << std::endl;

        result[chunk] = numDouble;
    }

    return result;
}


std::array<double, 8> GetParamsFromMasterKey(const std::string &master) {
    using namespace CryptoPP;
    HexEncoder encoder(new FileSink(std::cout));

    std::string digest;

    SHA3_512 hash;
    hash.Update(reinterpret_cast<const byte *>(master.data()), master.size());
    digest.resize(hash.DigestSize());
    hash.Final(reinterpret_cast<byte *>(&digest[0]));


    std::bitset<512> bits;
    size_t pos = 0;
    for (const auto b: digest) {
        for (int i = 7; i >= 0; --i) {
            bits[pos] = (b >> i) & 1;
            pos++;
        }
    }

    std::cout << "Master: " << master << std::endl;

    std::cout << "===== Hash =====" << std::endl;

    printBitset(bits);

    std::cout << "================" << std::endl;

    return splitTo8Doubles(bits);
}
