#ifndef NUMBERCONVERSION_H
#define NUMBERCONVERSION_H

#include <string>

// Linearly interpolate `raw` ∈ [0,1] to [A,B]; optionally avoid zero and take absolute value
double mapToRange(double raw, double A, double B, bool canBeZero = false, bool takeAbs = false);

// Extract `length` digits from the fractional part of `n`, starting at `startPosition`
int extractFractionDigits(double n, int startPosition, int length);

// Convert integer to string in base B (2 ≤ B ≤ 16)
template<int B>
std::string toBase(long long value);

// Parse string `s` in base B (2 ≤ B ≤ 16) into integer
template<int B>
long long fromBase(const std::string &s);

// Convenience conversions between binary, ternary, decimal, and hexadecimal
std::string fromBin2Tern(const std::string &v);
std::string fromBin2Hex(const std::string &v);

std::string toHex(long long v);
long long fromHex(const std::string &s);

std::string toBin(long long v);
long long fromBin(const std::string &s);

std::string toDec(long long v);
long long fromDec(const std::string &s);

std::string toTern(long long v);
long long fromTern(const std::string &s);

#endif // NUMBERCONVERSION_H
