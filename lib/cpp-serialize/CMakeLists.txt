cmake_minimum_required(VERSION 3.14)
project(cpp_serialize)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(xdrpp)

add_library(cpp_serialize src/xdr_abstract.h src/unmarshaler.cpp src/unmarshaler.h src/marshaler.cpp src/marshaler.h src/marshaler.t.hpp src/unmarshaler.t.hpp src/types.cpp src/types.h src/measurer.h src/measurer.cpp src/measurer.t.hpp)
target_link_libraries(cpp_serialize xdrpp)
set_target_properties(cpp_serialize PROPERTIES CXX_STANDARD 14)
#add_executable(test test/main.cpp test/types.cpp test/types.h xdr/xdr_abstract.h  xd/unmarshaler.t.hpp src/unmarshaler.cpp src/marshaler.cpp src/marshaler.h test/CreateAccountOp.cpp test/CreateAccountOp.h test/ManageSignerOp.cpp test/ManageSignerOp.h src/types.h src/types.cpp)

