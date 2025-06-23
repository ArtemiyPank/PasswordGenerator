cmake_minimum_required(VERSION 3.31)
project(PasswordGenerator)


set(CMAKE_CXX_STANDARD 20)

add_executable(PasswordGenerator
        include/Const.h
        include/Point.h
        include/PasswordGenerator.h
        src/PasswordGenerator.cpp
        include/LinearFunction.h
        src/LinearFunction.cpp
        include/TangentialFunction.h
        src/TangentialFunction.cpp
        include/IntersectionPoints.h
        src/IntersectionPoints.cpp
        src/HashesProcessing.cpp
        include/NumberConversion.h
        src/NumberConversion.cpp
        include/BitsProcessing.h
        src/BitsProcessing.cpp
        include/HexDigitMap.h
        src/HexDigitMap.cpp
        include/PasswordMaskGenerator.h
        src/PasswordMaskGenerator.cpp)

target_include_directories(PasswordGenerator PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(PasswordGenerator PRIVATE cryptopp)
