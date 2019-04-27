cmake_minimum_required(VERSION 3.12)
project(petzold_pw5e C)

set(CMAKE_C_STANDARD 11)

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DSTRICT -DWIN32_LEAN_AND_MEAN -DCMAKE_GENERATOR_PLATFORM=x64")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -DSTRICT -DWIN32_LEAN_AND_MEAN -DCMAKE_GENERATOR_PLATFORM=x64")

if (MSVC)
    # MSVC Compiler
else ()
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Wall -Wpedantic -Wextra")
    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -Wall -Wpedantic -Wextra")
endif ()

add_executable(HelloMsg WIN32
        "Chapter 01/0101 HelloMsg/HelloMsg.c")

add_executable(ScrnSize WIN32
        "Chapter 02/0201 ScrnSize/ScrnSize.c")
