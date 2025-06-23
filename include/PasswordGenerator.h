#ifndef PASSWORDGENERATOR_H
#define PASSWORDGENERATOR_H
#include <bitset>
#include <map>


std::string generatePassword(const std::bitset<256> &rowBits, std::map<char, int> hexDigitMap, const std::array<int, 16> &mask);


#endif //PASSWORDGENERATOR_H
