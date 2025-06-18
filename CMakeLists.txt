cmake_minimum_required(VERSION 3.31)
project(PasswordGenerator)

set(CMAKE_CXX_STANDARD 20)

add_executable(PasswordGenerator src/main.cpp
        include/PasswordGenerator.h
        src/PasswordGenerator.cpp
        include/LinearFunction.h
        src/LinearFunction.cpp
        include/TangentialFunction.h
        src/TangentialFunction.cpp
        include/FindIntersectionPoint.h
        src/FindIntersectionPoint.cpp
        include/IntersectionPoints.h
        src/IntersectionPoints.cpp
        include/Const.h
        include/Point.h)
