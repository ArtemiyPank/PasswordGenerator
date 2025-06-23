#ifndef HEXDIGITMAP_H
#define HEXDIGITMAP_H

#include <map>
#include <array>
#include <string>


std::array<double, 8> GetParamsFromMasterKey(const std::string& master);

std::array<double, 8> GetParamsFromMasterKey(const std::string &master);

std::array<int, 16> GetRowNumbersForMap(const std::string &master);

std::map<char, int> GetHexDigitMap(const std::string &master);

#endif //HEXDIGITMAP_H
