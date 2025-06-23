#include <array>
#include <bitset>
#include <iostream>
#include <ostream>

#include "PasswordMaskGenerator.h"
#include "Const.h"
#include "NumberConversion.h"

std::string FILE_NAME = "PasswordMaskGenerator";


// Generate a 16-element mask based on a 256-bit input bitset
std::array<int, 16> getPasswordMask(const std::bitset<256> &rowBits) {
    const std::string rowBitsString = rowBits.to_string();

    // Convert 4 segments of 16 bits each into a ternary string
    std::string tern_s;
    for (int i = 0; i < 4; ++i) {
        std::string substring = rowBits.to_string().substr(16 * i, 16);
        tern_s += fromBin2Tern(substring);
    }

    // Map the first 16 ternary characters ('0','1','2') to integers
    std::array<int, 16> bigPartsMask{};
    std::transform(tern_s.begin(), tern_s.begin() + 16, bigPartsMask.begin(),
                   [](const char c) { return c - '0'; });

    // Extract 16 bits for numbers/specials and map to integers (0 or 1)
    const std::string bin_s = rowBitsString.substr(129, 16);
    std::array<int, 16> numbersAndSpecialCharactersMask{};
    std::transform(bin_s.begin(), bin_s.begin() + 16, numbersAndSpecialCharactersMask.begin(),
                   [](const char c) { return c - '0'; });


    // Build the final mask: for bigPartsMask==2, choose 2 or 3 based on numSpecMask
    std::array<int, 16> mask{};
    for (int i = 0, j = 0; i < 16; ++i) {
        int type;
        if (bigPartsMask[i] == 2) {
            if (numbersAndSpecialCharactersMask[j]) {
                type = 2;
            } else {
                type = 3;
            }
            j++;
        } else {
            type = bigPartsMask[i];
        }
        mask[i] = type;
    }


    if (DEBUG && !isInException(FILE_NAME)) {
        std::cout << "---------------------- Mask ----------------------" << std::endl;
        for (const int type: mask) {
            std::cout << type;
        }
        std::cout << std::endl;
        std::cout << "====================== ====================== ======================" << std::endl;
    }

    return mask;
}
