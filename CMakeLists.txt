cmake_minimum_required(VERSION 3.17)
project(raytracing C)

set(CMAKE_C_STANDARD 99)

file(GLOB SOURCES *.h *.c)

add_executable(raytracing ${SOURCES})

if(WIN32)
    add_custom_command(
            TARGET raytracing POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${PROJECT_SOURCE_DIR}/pthread/pthreadVC3.dll
            ${PROJECT_SOURCE_DIR}/cmake-build-debug/pthreadVC3.dll)
    target_link_libraries(raytracing pthreadVC3)
else()
    target_link_libraries(raytracing pthread)
endif()

target_include_directories(raytracing PRIVATE pthread)
target_link_directories(raytracing PRIVATE pthread)
target_link_libraries(raytracing pthreadVC3)
