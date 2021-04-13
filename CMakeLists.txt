cmake_minimum_required(VERSION 3.17)
project(raytracing C)

set(CMAKE_C_STANDARD 99)

file(GLOB SOURCES *.h *.c)

add_executable(raytracing ${SOURCES})