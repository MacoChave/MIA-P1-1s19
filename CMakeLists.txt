cmake_minimum_required(VERSION 3.13)
project(MIA_P1_1s19 C)

set(CMAKE_C_STANDARD 11)

include_directories(interpreter)
include_directories(struct)

add_executable(MIA_P1_1s19
        interpreter/compiler.h
        struct/mlist.h
        struct/parameter.h
        struct/struct_disk.h
        main.c)
