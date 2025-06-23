#ifndef HEXDIGITMAP_H
#define HEXDIGITMAP_H

#include <map>
#include <array>
#include <string>

// Derive eight uniform parameters [0,1) from the master key
std::array<double, 8> GetParamsFromMasterKey(const std::string& master);

// Derive eight uniform parameters [0,1) from the master key (duplicate declaration)
std::array<double, 8> GetParamsFromMasterKey(const std::string &master);

// Generate 16 row indices for the map based on the master key
std::array<int, 16> GetRowNumbersForMap(const std::string &master);

// Build a mapping from hexadecimal digit characters to their corresponding row numbers
std::map<char, int> GetHexDigitMap(const std::string &master);

#endif // HEXDIGITMAP_H
