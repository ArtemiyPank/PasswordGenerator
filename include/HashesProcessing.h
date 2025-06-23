#ifndef CRYPTO_UTILS_H
#define CRYPTO_UTILS_H

#include <bitset>
#include <string>

// Computes the SHA3-512 hash of `master` and returns it as a 512-bit bitset.
std::bitset<512> GetHash_HSA_512(const std::string &master);

#endif // CRYPTO_UTILS_H
