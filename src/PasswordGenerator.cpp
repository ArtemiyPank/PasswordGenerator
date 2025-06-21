#include <iomanip>

#include "HexDigitMap.h"


static const std::string FILE_NAME = "PasswordGenerator";


int main() {


    const std::string master = "Master";

    std::map<char, int> hexDigitMap = GetHexDigitMap(master);

}



