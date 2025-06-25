# PasswordGenerator

**Repository:** [ArtemiyPank/PasswordGenerator](https://github.com/ArtemiyPank/PasswordGenerator)

## Table of Contents

* [Project Overview](#project-overview)
* [Features](#features)
* [Prerequisites](#prerequisites)
* [Code Structure](#code-structure)
* [Algorithm](#algorithm)

## Project Overview

PasswordGenerator is a C++20 command-line application that deterministically generates complex passwords using a single master password. From this master password, it builds a **Hex-Digit Map seed**, which serves as a personalized base for all further operations. For each service, the tool combines this Hex-Digit Map seed with the service name and applies **SHA3-512** hashing — first on the seed itself and then on each service name — to produce a unique, reproducible password. Changing the master password automatically rebuilds the Hex-Digit Map seed and allows to regenerate a password for each service.

## Features

* **Hex-Digit Map seed**: derives a consistent seed value from the master password via `GetHexDigitMap`, used as the foundation for all service passwords.
* **Service-specific hashing**: applies SHA3-512 to both the Hex-Digit Map seed and each service name to ensure unique, reproducible passwords.
* **Easy rotation**: updating the master password rebuilds the seed and all service passwords in one go.
* **Deterministic**: same master password + service name → same password.
* **Cryptographically secure**: uses SHA3-512 as an entropy source.
* **Mask-based character selection**: supports uppercase, lowercase, digits, and special characters.


## Prerequisites

* C++20 compiler (GCC 10+, Clang 10+, MSVC 2019+)
* CMake ≥ 3.31
* Crypto++ library
---


## Code Structure

### Const.h

* `DEBUG`, `NumberOfDigitsInHexDigitMap`, `DebugException` constants
* `isInException()` filter

### Point.h

```cpp
struct Point { double x, y; };
```

### NumberConversion.cpp

* `mapToRange()`: linear interpolation
* `extractFractionDigits()`: fractional-digit extraction
* `toBase<B>()` / `fromBase<B>()`: base conversion (2–16)
* Convenience wrappers: bin/hex/dec/tern

### BitsProcessing.cpp

* Contains utilities to interpret raw hash outputs as bitsets and convert fixed-size chunks into uniform floating-point parameters using IEEE‑754 bit manipulation.

### HashesProcessing.cpp

* `GetHash_SHA3_512()`: SHA3-512 digest → `bitset<512>`

### HexDigitMap.cpp

**Hex-Digit Map**:

1. Split master-hash bits into eight 64-bit blocks, map to doubles → parameters $p_0\dots p_7$.


2. Instantiate functions:

$f_{\tan}(x)=g\cdot\frac{c\,\tan(a x+b)+d}{f},\quad f_{lin}(x)=k x+h.$

3. Vertical asymptotes:

$x_n=\frac{\tfrac{\pi}{2}+(n-1)\pi-b}{a}.$

4. Function Intersections Visualization
   

   ![Function Intersections Visualization](https://raw.githubusercontent.com/ArtemiyPank/ForReadme/main/images/Intersections_of_tangential_and_linear_functions.png)
   * yellow - $f_{tan}(x)$ (tangential function)   
   * blue - $f_{lin}(x)$ (linear function) 
   * red - asymptotes of $f_{tan}(x)$ 
   * white intersection points  
   

5. Compute 16 intersections over successive intervals between asymptotes.


6. Extract two fractional digits from each $(x,y)$ → 16 integers (using `startPosition=3`, `length=2`).


7. Map hex digits '0'–'F' to these values → hex-digit map.

### LinearFunction.cpp

* Represents $f_{lin}(x)=k x+h$
* Parameter clamping, `func(x)`, intersections with axes

### TangentialFunction.cpp

* Represents $f_{tan}(x)=g,(c,\tan(a x+b)+d)$
* Parameter clamping, `func(x)`, `GetAsymptoteByNumber(n)`

### IntersectionPoints.cpp

* Uses bisection to find intersections of functions ($f_{tan}(x)-f_{lin}(x) = 0$) over each asymptote interval

### PasswordMaskGenerator.cpp

* Builds a 16-element mask from 256 bits

### PasswordGenerator.cpp

* Orchestrates: \[hash(master key) → hex-digit map\] → \[hash(app name) → mask\] → password
---


## Algorithm

### 1. Master Key → Hex-Digit Map

1. Compute digest:
   $H=\mathrm{SHA3\_{512}}(\text{masterKey})\;(512\text{-bit}).$


2. Convert to `bitset<512>`, split into eight 64-bit chunks.


3. For each chunk:

   * Mantissa: $m=\text{bits}\_{51:0}$
   * Construct: $u=((1023\ll52)|m)$ → IEEE-754 double $d=\mathrm{bit\_cast}(u)$.
   * Parameter: $p\_i=d-1\in[0,1)$.


4. Instantiate functions with $p\_0\dots p\_5$:


   $f_{tan}(x)=g\cdot\frac{c\,\tan(a x+b)+d}{f},\quad f_{lin}(x)=k x+h.$


5. Asymptotes:
   $x_n=\frac{\tfrac{\pi}{2}+(n-1)\pi-b}{a}.$


6. Find 16 intersections via bisection in each interval.


7. Extract two fractional digits from each intersection’s $(x,y)$ → 16 integers.


8. Map digits '0'–'F' to these values → final hex-digit map.

### 2. App Name → Mask

1. Compute digest:
   $H'=\mathrm{SHA3\_{512}}(\text{appName})\;(512\text{-bit}).$


2. Split into `low` / `high` (256 bits each).


3. From `low`:
   * Four 64-bit segments → base-3 → 64-char string.
   * First 16 chars → `bigPartsMask[i] in {0,1,2}`.
   * Bits 129–144 → `numSpecMask[i] in {0,1}`.
   * Final mask:

$$\text{mask}[i]=\begin{cases}
2,&\text{if }m_i=2\text{ and }s_j=1,\\
3,&\text{if }m_i=2\text{ and }s_j=0,\\
m_i,&\text{otherwise}.
\end{cases}$$

### 3. Mask → Password

1. From `high`: sixteen 16-bit → two hex chars each → 32-char hex string.


2. Left-pad to 16 chars if needed.


3. Map each char to two-digit code via hex-digit map → `encodedPassword`.


4. For each position:
   * Parse two-digit code → integer.
   * Select character set: uppercase (0), lowercase (1), digits (2), specials (3).
   * Character = set[code%set.size()].


5. The result is a 16-character password.

