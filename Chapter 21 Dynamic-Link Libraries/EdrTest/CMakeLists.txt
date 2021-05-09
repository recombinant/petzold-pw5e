cmake_minimum_required(VERSION 3.12)
project(petzold_pw5e C)
# set(CMAKE_VERBOSE_MAKEFILE ON)#

set(CMAKE_C_STANDARD 11)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DSTRICT -DCMAKE_GENERATOR_PLATFORM=x64")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D_WIN32_WINNT=0x0601 -DWINVER=0x0601")

if (MSVC)
    # MSVC Compiler
else ()
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Wall -Wpedantic -Wextra")
    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -Wall -Wpedantic -Wextra")
endif ()

add_executable(EdrTest WIN32 "EdrTest.c")

#add_library(EdrLib SHARED)
#target_sources(EdrLib PRIVATE
#        "Chapter 21 Dynamic-Link Libraries/EdrTest/EdrLib.h"
#        "Chapter 21 Dynamic-Link Libraries/EdrTest/EdrLib.c")
