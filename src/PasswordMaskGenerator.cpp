#include <array>
#include <bitset>

#include "PasswordMaskGenerator.h"

#include <iostream>
#include <ostream>

#include "Const.h"
#include "NumberConversion.h"

std::string FILE_NAME = "PasswordMaskGenerator";


std::array<int, 16> getPasswordMask(const std::bitset<256> &rowBits) {
    const std::string rowBitsString = rowBits.to_string();

    const std::string tern_s = fromBin2Tern(rowBitsString.substr(0, 64));


    std::array<int, 16> bigPartsMask{};
    std::transform(tern_s.begin(), tern_s.begin() + 16, bigPartsMask.begin(),
                   [](const char c) { return c - '0'; });


    const std::string bin_s = rowBitsString.substr(129, 64);
    std::array<int, 16> numbersAndSpecialCharactersMask{};
    std::transform(bin_s.begin(), bin_s.begin() + 16, numbersAndSpecialCharactersMask.begin(),
                   [](const char c) { return c - '0'; });


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
