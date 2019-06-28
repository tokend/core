cmake_minimum_required(VERSION 3.2.2)

project(xdrpp CXX)

set(CMAKE_CXX_STANDARD 14)

#set_target_properties(xdrpp PROPERTIES LINKER_LANGUAGE CXX)

add_library(xdrpp marshal.h printer.h message.h marshal.cpp build_endian.h)