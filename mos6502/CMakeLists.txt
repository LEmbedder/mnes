cmake_minimum_required(VERSION 3.1.0)
project(mos6502)

set(SRC bitwise.cpp branch.cpp instructions.cpp jump.cpp math.cpp mos6502.cpp registers.cpp
	stack.cpp storage.cpp system.cpp)
add_library(${PROJECT_NAME} ${SRC})

add_executable(${PROJECT_NAME}_test test.cpp)
target_link_libraries(${PROJECT_NAME}_test ${PROJECT_NAME})
