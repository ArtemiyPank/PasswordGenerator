# PasswordGenerator

**Repository:** [ArtemiyPank/PasswordGenerator](https://github.com/ArtemiyPank/PasswordGenerator)

## Table of Contents

* [Project Overview](#project-overview)
* [Features](#features)
* [Prerequisites](#prerequisites)
* [Usage](#usage)
* [Code Structure](#code-structure)
* [Algorithm Explanation](#algorithm-explanation)

## Project Overview

PasswordGenerator is a C++20 command-line application that deterministically generates complex passwords from a master key and application name. It leverages SHA3‑512 hashing, bit-level transformations, and mathematical function intersections to produce reproducible, secure passwords without storing them.

## Features

* **Deterministic**: same inputs → same password
* **Cryptographically secure**: uses SHA3‑512 as an entropy source
* **Mask-based character selection**: uppercase, lowercase, digits, specials
* **Modular design**: separate components for hashing, bit processing, conversion, function intersection, mask generation

## Prerequisites

* C++20 compiler (GCC 10+, Clang 10+, MSVC 2019+)
* CMake ≥ 3.31
* Crypto++ library

## Usage

Adjust `main()` or integrate library functions:

1. Choose a **master key** (string).
2. Choose an **application name** (string).
3. Call `GetHexDigitMap(masterKey)` → hex→row map.
4. Compute `GetHash_SHA3_512(appName)` → 512­bit `bitset`.
5. Split into `low`/`high` (256 bits each).
6. Generate **mask**: `getPasswordMask(low)` → 16­element array.
7. Generate **password**: `generatePassword(high, hexMap, mask)`.
8. Optionally display with `printPasswordPretty(password)`.

## Code Structure

### include/Const.h

* `DEBUG`, `NumberOfDigitsInHexDigitMap` constants
* `DebugException`, `isInException()` filter

### include/Point.h

```cpp
struct Point { double x, y; };
```

### include/NumberConversion.h & src/NumberConversion.cpp

* `mapToRange()`: linear interpolation
* `extractFractionDigits()`: fractional-digit extraction
* `toBase<B>()`/`fromBase<B>()`: base conversion (2–16)
* Convenience wrappers: bin/hex/dec/tern

### include/BitsProcessing.h & src/BitsProcessing.cpp

* `getBitset512FromString()`: raw bytes → `bitset<512>`
* `bitsetToDouble()`: reinterpret 64 bits as IEEE‑754 double
* `bitsToUniform01()`: map bits → uniform \[0,1)
* `splitTo8Doubles()`: eight uniform parameters

### include/HashesProcessing.h & src/HashesProcessing.cpp

* `GetHash_SHA3_512()`: SHA3‑512 digest → `bitset<512>`

### include/HexDigitMap.h & src/HexDigitMap.cpp

* **Hex‑Digit Map**:

    * Split master‑hash bits into eight 64‑bit blocks, map to double → parameters $p_0…p_7$.
    * Instantiate:

      $$
      f_{\tan}(x) = g \cdot \frac{c\,\tan(a x + b) + d}{f},
      \quad f_{lin}(x) = k x + h.
      $$
    * Vertical asymptotes:

      $$
      x_n = \frac{\frac{\pi}{2} + (n - 1)\pi - b}{a}.
      $$
    * Compute 16 intersections over successive intervals between asymptotes.
    * Extract three fractional digits from each $x,y$ → 16 integer.
    * Map hex digits '0'–'F' to these values → hex‑digit map.

### include/LinearFunction.h & src/LinearFunction.cpp

* Represents $f_{lin}(x)=k x + h$
* Parameter clamping, `func(x)`, intercepts

### include/TangentialFunction.h & src/TangentialFunction.cpp

* Represents $f_{tan}(x)=g\,(c\,\tan(a x + b)+d)/f$
* Parameter clamping, `func(x)`, `GetAsymptoteByNumber(n)`

### include/IntersectionPoints.h & src/IntersectionPoints.cpp

* Bisection to find intersections of $f_{\tan}-f_{lin}$ over each asymptote interval

### include/PasswordMaskGenerator.h & src/PasswordMaskGenerator.cpp

* Builds a 16‑element mask from 256 bits: ternary + numeric/special logic

### include/PasswordGenerator.h & src/PasswordGenerator.cpp

* Orchestrates: hash → split bits → mask → password → pretty print

## Algorithm Explanation

### 1. Master Key → Hex‑Digit Map

1. Compute digest:
   $ H = \mathrm{SHA3\_512}(\text{masterKey}) \; (512\text{-bit}).$
2. Convert to `bitset<512>`, split into eight 64‑bit chunks.
3. For each chunk:

    * Mantissa $m = \text{bits}_{51:0}$
    * Construct $u = ((1023 \ll 52) | m)$ → IEEE‑754 double $d = \mathit{bit\_cast}(u)$.
    * Parameter $p_i = d - 1 \in [0,1)$.
4. Use $p_0…p_5$ in:

   $$
   f_{\tan}(x) = g \;\frac{c\,\tan(a x + b)+d}{f},
   \quad f_{lin}(x)=k x + h.
   $$
5. Asymptotes:

   $$
   x_n = \frac{\frac{\pi}{2} + (n-1)\pi - b}{a}.
   $$
6. Find 16 intersections via bisection in each interval.
7. Extract three fractional digits from each intersection’s $x,y$ → 16 ints.
8. Map ‘0’–‘F’ to these values → the final hex ‑ digit map.

### 2. App Name → Mask

1. Digest $=\mathrm{SHA3\_512}(\text{appName})$, split into `low`/`high` 256 bits.
2. From `low`:

    * Four 64‑bit segments → base‑3 → 64‑char string.
    * First 16 chars → `bigPartsMask[i]\in\{0,1,2\}`.
    * Bits 129–144 → `numSpecMask[i]\in\{0,1\}`.
    * Final mask:

      $$
      \text{mask}[i] = \begin{cases}
      2,&\text{if }m_i=2\text{ and }s_j=1,\\
      3,&\text{if }m_i=2\text{ and }s_j=0,\\
      m_i,&\text{otherwise}.
      \end{cases}
      $$

### 3. Mask → Password

1. From `high`: sixteen 16‑bit → two hex chars each → 32‑char hex string.
2. Left‑pad to 16 chars if needed.
3. Map each char to two‑digit code via a hex‑digit map → `encodedPassword`.
4. For each position:

    * Parse two‑digit code → integer.
    * Select a set: uppercase (0), lowercase (1), digits (2), specials (3).
    * Char = set\[code % set.size()].
5. Result: 16‑character password.

*End of algorithm explanation.*
