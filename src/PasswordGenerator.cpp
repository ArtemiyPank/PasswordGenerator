#include <algorithm>
#include <bitset>
#include <cstdint>
#include <iomanip>

#include "HashesProcessing.h"
#include "HexDigitMap.h"
#include "PasswordMaskGenerator.h"


static const std::string FILE_NAME = "PasswordGenerator";



std::string generatePassword (std::bitset<256> rowBits, std::array<int, 16> mask) {


    std::string password;

    return password;
}

int main() {


    const std::string master = "Master";

    const std::string appName = "AppName";

    std::map<char, int> hexDigitMap = GetHexDigitMap(master);


    std::bitset<512> appNameHashInBits = GetHash_HSA_512(appName);

    // const uint64_t uint64 = appNameHashInBits.to_ullong();

    std::bitset<256> low, high;

    for (std::size_t i = 0; i < 256; i++) {
        low[i] = appNameHashInBits[i];
        high[i] = appNameHashInBits[i + 256];
    }


    std::array<int, 16> mask = getPasswordMask(low);




    std::string password = generatePassword(high, mask);



    return 0;

}




