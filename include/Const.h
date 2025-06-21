//
// Created by artemiypank on 6/18/25.
//

#ifndef CONST_H
#define CONST_H
#include <algorithm>
#include <vector>


inline constexpr double Pi = 3.14159265358979323846;

inline int NumberOfDigitsInHexDigitMap = 2;


constexpr bool DEBUG = true;

constexpr std::vector<std::string> DebugException = {};

inline bool isInException(const std::string& fileName) {
    return std::ranges::find(DebugException, fileName) != DebugException.end();
}




#endif //CONST_H
