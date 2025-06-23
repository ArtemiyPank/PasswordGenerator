#ifndef CRYPTO_UTILS_H
#define CRYPTO_UTILS_H

#include <bitset>
#include <string>


std::bitset<512> GetHash_HSA_512(const std::string &master);

#endif // CRYPTO_UTILS_H
