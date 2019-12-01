cmake_minimum_required(VERSION 3.15)
project(abstract_algebra)

set(CMAKE_CXX_STANDARD 14)

include_directories(
        ${PROJECT_SOURCE_DIR}
        ${BigInt}
        ${ModArithmetic}
        ${MontgomeryReduction}
)

add_executable(abstract_algebra main.cpp BigInt/BigInt.cpp BigInt/BigInt.h
        ModArithmetic/ModArithmetic.h MontgomeryReduction/MontgomeryReducer.h MontgomeryReduction/MontgomeryReducer.cpp)