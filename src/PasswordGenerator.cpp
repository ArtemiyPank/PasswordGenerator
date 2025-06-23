#include <bitset>
#include <iomanip>
#include <iostream>

#include "PasswordMaskGenerator.h"
#include "HashesProcessing.h"
#include "HexDigitMap.h"
#include "NumberConversion.h"

const std::string FILE_NAME = "PasswordGenerator";

// Print the password in a styled box
void printPasswordPretty(const std::string &password) {

    // ANSI escape codes for colored, bold output
    constexpr char RESET[] = "\033[0m";
    constexpr char BOLD[] = "\033[1m";
    constexpr char FG_CYAN[] = "\033[36m";

    const size_t width = password.size() + 4;
    const std::string border(width, '-');

    std::cout << BOLD << FG_CYAN
            << "┌" << border << "┐\n"
            << "│  " << password << "  │\n"
            << "└" << border << "┘\n"
            << RESET;
}

// Character sets used for mask application
const std::string capitalLetters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const std::string lowercaseLetters = "abcdefghijklmnopqrstuvwxyz";
const std::string numbers = "0123456789";
const std::string specialCharacters = "-_+=.@#^&*~`";

// Apply the mask to two-digit codes, producing the final password characters
std::string applyPasswordMask(const std::string &encodedPassword, const std::array<int, 16> &mask) {
    std::string password;
    for (int i = 0; i < 16; ++i) {
        int num = std::stoi(encodedPassword.substr(2 * i, 2));
        switch (mask[i]) {
            case 0: password += capitalLetters[num % capitalLetters.size()];
                break;
            case 1: password += lowercaseLetters[num % lowercaseLetters.size()];
                break;
            case 2: password += numbers[num % numbers.size()];
                break;
            case 3: password += specialCharacters[num % specialCharacters.size()];
                break;
        }
    }
    return password;
}

// Generate the password by converting bits → hex → codes → mask
std::string generatePassword(const std::bitset<256> &rowBits,
                             const std::map<char, int> &hexDigitMap,
                             const std::array<int, 16> &mask) {
    // Convert each 16-bit segment to hex digits
    std::string hexString;
    std::string bits = rowBits.to_string();
    for (int i = 0; i < 16; ++i) {
        hexString += fromBin2Hex(bits.substr(16 * i, 16));
    }
    // Left-pad if necessary
    if (hexString.size() < 16) {
        hexString.insert(0, 16 - hexString.size(), '0');
    }

    // Map each hex char to a two-digit code
    std::string encodedPassword;
    encodedPassword.reserve(32);
    for (char hc: hexString) {
        int val = hexDigitMap.at(hc);
        encodedPassword += (val < 10 ? "0" : "") + std::to_string(val);
    }

    // Apply mask to produce the final password
    return applyPasswordMask(encodedPassword, mask);
}

int main() {
    const std::string master = "Master";
    const std::string appName = "Google";

    std::map<char, int> hexDigitMap = GetHexDigitMap(master);

    std::bitset<512> appNameHashInBits = GetHash_HSA_512(appName);
    std::bitset<256> low, high;
    for (std::size_t i = 0; i < 256; i++) {
        low[i] = appNameHashInBits[i];
        high[i] = appNameHashInBits[i + 256];
    }

    const std::array<int, 16> mask = getPasswordMask(low);

    const std::string password = generatePassword(high, hexDigitMap, mask);


    std::cout << "Master key: " << master << std::endl;
    std::cout << "App name: " << appName << std::endl;
    printPasswordPretty(password);

    return 0;
}
