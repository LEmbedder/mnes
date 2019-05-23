cmake_minimum_required(VERSION 3.1.0)
project(mos6502)

set(SRC debug.cpp instructions.cpp mos6502.cpp)
add_library(${PROJECT_NAME} ${SRC})
