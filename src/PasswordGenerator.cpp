#include <bitset>
#include <cstdint>
#include <iomanip>
#include <iostream>

#include "HashesProcessing.h"
#include "HexDigitMap.h"
#include "NumberConversion.h"
#include "PasswordMaskGenerator.h"


const std::string FILE_NAME = "PasswordGenerator";


constexpr char RESET[]   = "\033[0m";
constexpr char BOLD[]    = "\033[1m";
constexpr char FG_CYAN[] = "\033[36m";

void printPasswordPretty(const std::string& password) {
    const size_t w = password.size() + 4;

    const std::string border(w, '-');

    std::cout << BOLD << FG_CYAN
        << "┌" << border << "┐\n"
        << "│  " << password << "  │\n"
        << "└" << border << "┘\n"
        << RESET
    ;
}

const std::string capitalLetters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

const std::string lowercaseLetters = "abcdefghijklmnopqrstuvwxyz";

const std::string numbers = "0123456789";

const std::string specialCharacters = "-_+=.@#^&*~`";



std::string applyPasswordMask(const std::string encodedPassword, const std::array<int, 16> &mask) {
    std::string password;

    for (int i = 0; i < 16; ++i) {
        const int num = std::stoi(encodedPassword.substr(2*i, 2));
        if (mask[i] == 0) {
            password += capitalLetters[num % capitalLetters.size()];
        } else if (mask[i] == 1) {
            password += lowercaseLetters[num % lowercaseLetters.size()];
        } else if (mask[i] == 2) {
            password += numbers[num % numbers.size()];
        } else if (mask[i] == 3) {
            password += specialCharacters[num % specialCharacters.size()];
        }
    }

    return password;
}

std::string generatePassword(const std::bitset<256> &rowBits, std::map<char, int> hexDigitMap, const std::array<int, 16> &mask) {
    std::string hexString;

    for (int i = 0; i < 16; ++i) {
        std::string substring = rowBits.to_string().substr(16 * i, 16);
        hexString += fromBin2Hex(substring);
    }

    if (hexString.size() < 16) hexString = std::string(16 - hexString.size(), '0') + hexString;

    std::string encodedPassword;
    for (char hexCharacter: hexString) {
        const std::string encryptedCharacter = hexDigitMap[hexCharacter] < 10
                                                   ? "0" + std::to_string(hexDigitMap[hexCharacter])
                                                   : std::to_string(hexDigitMap[hexCharacter]);
        encodedPassword += encryptedCharacter;
    }

    std::string password = applyPasswordMask(encodedPassword, mask);

    return password;
}

int main() {
    const std::string master = "Master";

    const std::string appName = "AppName";

    std::map<char, int> hexDigitMap = GetHexDigitMap(master);


    std::bitset<512> appNameHashInBits = GetHash_HSA_512(appName);


    std::bitset<256> low, high;

    for (std::size_t i = 0; i < 256; i++) {
        low[i] = appNameHashInBits[i];
        high[i] = appNameHashInBits[i + 256];
    }

    const std::array<int, 16> mask = getPasswordMask(low);

    const std::string password = generatePassword(high, hexDigitMap, mask);

    printPasswordPretty(password);

    return 0;
}
