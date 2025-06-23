#include <cmath>
#include <string>
#include <algorithm>
#include <stdexcept>

#include "NumberConversion.h"

static const std::string FILE_NAME = "NumberConversion";

// Linearly interpolate `raw` ∈ [0,1] to [A,B]; optionally avoid zero and take absolute value
double mapToRange(double raw, double A, double B, bool canBeZero, bool takeAbs) {
    double res = raw * (B - A) + A;
    if (!canBeZero && res == 0.0)
        res = std::nextafter(0.0, 1.0); // shift away from zero
    if (takeAbs)
        res = std::fabs(res);
    return res;
}

// Extract `length` digits from the fractional part of `n`, starting at `startPosition`
int extractFractionDigits(double n, int startPosition, int length) {
    n = std::fmod(std::fabs(n), std::pow(10, -(startPosition - 1)))
        * std::pow(10, (startPosition - 1));
    n = std::floor(n * std::pow(10, length));
    return static_cast<int>(n);
}

// Convert integer to string in base B (2 ≤ B ≤ 16)
template<int B>
std::string toBase(long long value) {
    static_assert(B >= 2 && B <= 16, "Base must be between 2 and 16");
    if (value == 0)
        return "0";
    static constexpr char digits[] = "0123456789ABCDEF";
    bool neg = value < 0;
    unsigned long long v = neg ? -value : value;
    std::string s;
    while (v) {
        s.push_back(digits[v % B]);
        v /= B;
    }
    if (neg)
        s.push_back('-');
    std::reverse(s.begin(), s.end());
    return s;
}

// Convert string `s` in base B (2 ≤ B ≤ 16) to integer
template<int B>
long long fromBase(const std::string &s) {
    static_assert(B >= 2 && B <= 16, "Base must be between 2 and 16");
    size_t i = 0;
    bool neg = false;
    if (s[0] == '-') {
        neg = true;
        ++i;
    }
    if (i >= s.size())
        throw std::invalid_argument("Empty string");
    long long result = 0;
    for (; i < s.size(); ++i) {
        char c = s[i];
        int d = (c >= '0' && c <= '9')
                    ? c - '0'
                    : (c >= 'A' && c <= 'F')
                          ? 10 + c - 'A'
                          : (c >= 'a' && c <= 'f')
                                ? 10 + c - 'a'
                                : throw std::invalid_argument("Invalid digit");
        if (d >= B)
            throw std::invalid_argument("Digit out of range");
        result = result * B + d;
    }
    return neg ? -result : result;
}

// Helper conversions between bases
std::string fromBin2Tern(const std::string &v) { return toBase<3>(fromBase<2>(v)); }
std::string fromBin2Hex(const std::string &v) { return toBase<16>(fromBase<2>(v)); }

std::string toHex(const long long v) { return toBase<16>(v); }
long long fromHex(const std::string &s) { return fromBase<16>(s); }

std::string toBin(const long long v) { return toBase<2>(v); }
long long fromBin(const std::string &s) { return fromBase<2>(s); }

std::string toDec(const long long v) { return toBase<10>(v); }
long long fromDec(const std::string &s) { return fromBase<10>(s); }

std::string toTern(const long long v) { return toBase<3>(v); }
long long fromTern(const std::string &s) { return fromBase<3>(s); }
