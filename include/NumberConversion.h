#ifndef NUMBERCONVERSION_H
#define NUMBERCONVERSION_H

double mapToRange(double raw, double A, double B, bool canBeZero = false, bool takeAbs = false);

int extractFractionDigits(double n, int startPosition, int length);

template<int B>
std::string toBase(long long value);

template<int B>
long long fromBase(const std::string &s);



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

#endif //NUMBERCONVERSION_H
