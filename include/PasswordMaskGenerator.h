#ifndef PASSWORDMASKGENERATOR_H
#define PASSWORDMASKGENERATOR_H
#include <array>
#include <bitset>

std::array<int, 16> getPasswordMask(const std::bitset<256> &rowBits);

#endif //PASSWORDMASKGENERATOR_H
