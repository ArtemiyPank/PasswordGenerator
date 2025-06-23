#ifndef PASSWORDMASKGENERATOR_H
#define PASSWORDMASKGENERATOR_H

#include <array>
#include <bitset>

// Generate a 16-element mask from a 256-bit input bitset.
// Each element indicates the character type for the password (0 - uppercase, 1- lowercase, 2 - digit, 3 - special).
std::array<int, 16> getPasswordMask(const std::bitset<256> &rowBits);

#endif // PASSWORDMASKGENERATOR_H
