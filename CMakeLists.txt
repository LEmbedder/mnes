cmake_minimum_required(VERSION 3.1.0)
project(mnes)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

add_subdirectory(mos6502)
set(SRC main.cpp)
include_directories(mos6502)
add_executable(${PROJECT_NAME} ${SRC})
target_link_libraries(${PROJECT_NAME} mos6502)
