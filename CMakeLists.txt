cmake_minimum_required(VERSION 3.8)
project(stellar)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(lib)
add_subdirectory(src)
add_subdirectory(lib/crow)
add_subdirectory(lib/libsodium)
add_subdirectory(lib/cpp-serialize)
add_subdirectory(lib/gtest)