#ifndef PASSWORDGENERATOR_H
#define PASSWORDGENERATOR_H

#include <bitset>
#include <map>
#include <array>
#include <string>


// Print the password in a styled box
void printPasswordPretty(const std::string &password);

// Apply a mask to an encoded two-digit-per-char string to build the final password
std::string applyPasswordMask(const std::string &encodedPassword,
                              const std::array<int, 16> &mask);

// Generate a password by converting bits → hex → codes → mask
std::string generatePassword(const std::bitset<256> &rowBits,
                             const std::map<char, int> &hexDigitMap,
                             const std::array<int, 16> &mask);


#endif //PASSWORDGENERATOR_H
