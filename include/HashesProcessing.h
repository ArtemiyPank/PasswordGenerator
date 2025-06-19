#ifndef CRYPTO_UTILS_H
#define CRYPTO_UTILS_H

#include <array>
#include <bitset>
#include <string>

void printBitset_512(const std::bitset<512>& bits);

double bitsetToDouble(const std::bitset<64>& bits);

std::array<double, 8> splitTo8Doubles(const std::bitset<512>& bits);

std::array<double, 8> GetParamsFromMasterKey(const std::string& master);

#endif // CRYPTO_UTILS_H
