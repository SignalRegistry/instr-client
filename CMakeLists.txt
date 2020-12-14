cmake_minimum_required(VERSION 2.8.9)
if (WIN32)
    set(CMAKE_GENERATOR_PLATFORM win32)
endif (WIN32)

project (instr-client)

# compile
add_executable(instr-client main.c)