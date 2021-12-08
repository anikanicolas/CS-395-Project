cmake_minimum_required(VERSION 3.20)
project(CS_395_Project)

set(CMAKE_CXX_STANDARD 17)

add_executable(processor processor.cpp utils.cpp idecode.cpp rfetch.cpp iexecute.cpp maccess.cpp rwriteback.cpp)
