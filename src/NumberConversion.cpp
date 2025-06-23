#include <cmath>
#include <string>
#include <algorithm>
#include <stdexcept>

#include "NumberConversion.h"



static const std::string FILE_NAME = "NumberConversion";

// алгоритм линейной интерполяции
double mapToRange(double raw, double A, double B, bool canBeZero, bool takeAbs) {
    double rez = raw * (B - A) + A;

    if (!canBeZero && rez == 0.0) rez = std::nextafter(0.0, 1.0);

    if (takeAbs) rez = std::fabs(rez);

    return rez;
}

// Извлечение последовательности цифр из дробной части числа `n`
int extractFractionDigits(double n, int startPosition, int length) {
    // отбрасываем всё до startPosition и сдвигаем к нулю
    n = fmod(std::fabs(n), std::pow(10, -(startPosition - 1))) * pow(10, (startPosition - 1));

    // оставляем столько цифр, сколько нужно
    n = floor(n * std::pow(10, length));

    return static_cast<int>(n);
}


// Преобразует целое в строку в системе с основанием B (2 ≤ B ≤ 16).
template<int B>
std::string toBase(const long long value) {
    static_assert(B >= 2 && B <= 16, "Base must be between 2 and 16");
    if (value == 0) return "0";

    static constexpr char digits[] = "0123456789ABCDEF";
    const bool neg = value < 0;
    unsigned int v = neg ? -value : value;
    std::string s;

    while (v) {
        s.push_back(digits[v % B]);
        v /= B;
    }
    if (neg) s.push_back('-');
    std::ranges::reverse(s);
    return s;
}

// Преобразует строку s в системе с основанием B (2 ≤ B ≤ 16) и возвращает int.
template<int B>
long long fromBase(const std::string &s) {
    static_assert(B >= 2 && B <= 16, "Base must be between 2 and 16");
    size_t i = 0;

    bool neg = false;

    if (s[0] == '-') {
        neg = (s[i] == '-');
        ++i;
    }

    if (i >= s.size())
        throw std::invalid_argument("Empty string");

    long long result = 0;
    for (; i < s.size(); ++i) {
        const char c = s[i];
        int d = 0;
        if (c >= '0' && c <= '9') d = c - '0';
        else if (c >= 'A' && c <= 'F') d = 10 + c - 'A';
        else if (c >= 'a' && c <= 'f') d = 10 + c - 'a';
        else throw std::invalid_argument("Invalid digit");

        if (d >= B)
            throw std::invalid_argument("Digit out of range");
        result = result * B + d;
    }
    return neg ? -result : result;
}


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

