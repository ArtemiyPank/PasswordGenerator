#ifndef PASSWORDGENERATOR_H
#define PASSWORDGENERATOR_H
#include <bitset>


std::string generatePassword (std::bitset<256> rowBits, std::array<int, 16> mask);


#endif //PASSWORDGENERATOR_H
