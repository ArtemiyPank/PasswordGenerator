#ifndef CONST_H
#define CONST_H

#include <algorithm>
#include <vector>
#include <string>
#include <ranges>

// Number of digits reserved per hex entry in the map (e.g., “00”–“15”)
inline constexpr int NumberOfDigitsInHexDigitMap = 2;

// Global flag to enable or disable debug output
constexpr bool DEBUG = false;

// List of file names for which debug logging is skipped
inline constexpr std::vector<std::string> DebugException = {};

/// Determine whether `fileName` is exempt from debug logging
inline bool isInException(const std::string &fileName) {
    return std::ranges::find(DebugException, fileName) != DebugException.end();
}

#endif // CONST_H
