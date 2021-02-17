cmake_minimum_required(VERSION 3.10)

project(snakenn VERSION 0.1)
set(CMAKE_CXX_STANDARD 14)
set(EXEC snakenn)

include_directories(includes)

file(GLOB SOURCES src/*.cpp)

add_executable(${EXEC} ${SOURCES})