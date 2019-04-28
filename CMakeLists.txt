cmake_minimum_required(VERSION 3.12)
project(petzold_pw5e C)

set(CMAKE_C_STANDARD 11)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DSTRICT -DCMAKE_GENERATOR_PLATFORM=x64")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D_WIN32_WINNT=0x0601 -DWINVER=0x0601")

if (MSVC)
    # MSVC Compiler
else ()
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Wall -Wpedantic -Wextra")
    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -Wall -Wpedantic -Wextra")
endif ()

# =============================================================================
# ================================================================== Chapter 01

add_executable(001_HelloMsg WIN32
        "Chapter 01 Getting Started/01 HelloMsg/HelloMsg.c")

# ================================================================== Chapter 02

add_executable(002_ScrnSize WIN32
        "Chapter 02 An Introduction to Unicode/01 ScrnSize/ScrnSize.c")

# ================================================================== Chapter 03
# winmm.lib    - required library
# HelloWin.wav - to be copied to exe directory

add_executable(003_HelloWin WIN32
        "Chapter 03 Windows and Messages/01 HelloWin/HelloWin.c"
        "Chapter 03 Windows and Messages/01 HelloWin/HelloWin.wav")
target_link_libraries(003_HelloWin winmm.lib)
add_custom_command(
        OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/HelloWin.wav"
        COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/Chapter 03 Windows and Messages/01 HelloWin/HelloWin.wav" "${CMAKE_CURRENT_BINARY_DIR}"
        COMMENT "Copying HelloWin.wav to exe directory"
        DEPENDS "Chapter 03 Windows and Messages/01 HelloWin/HelloWin.wav")
add_custom_target(custom_target_003 ALL
        DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/HelloWin.wav")
add_dependencies(003_HelloWin custom_target_003)

# ================================================================== Chapter 04
# -------------------------------------------------------------- 04/01 SysMets1

add_executable(004_SysMets1 WIN32
        "Chapter 04 An Exercise in Text Output/01 SysMets1/SysMets1.c"
        "Chapter 04 An Exercise in Text Output/01 SysMets1/SysMets.h")
target_include_directories(004_SysMets1 PUBLIC "Chapter 04 An Exercise in Text Output/01 SysMets1")

# -------------------------------------------------------------- 04/02 SysMets2
#                                                uses header file from SysMets1

add_executable(005_SysMets2 WIN32
        "Chapter 04 An Exercise in Text Output/02 SysMets2/SysMets2.c"
        "Chapter 04 An Exercise in Text Output/01 SysMets1/SysMets.h")
target_include_directories(005_SysMets2 PUBLIC "Chapter 04 An Exercise in Text Output/01 SysMets1")

# -------------------------------------------------------------- 04/03 SysMets3
#                                                uses header file from SysMets1

add_executable(006_SysMets3 WIN32
        "Chapter 04 An Exercise in Text Output/03 SysMets3/SysMets3.c"
        "Chapter 04 An Exercise in Text Output/01 SysMets1/SysMets.h")
target_include_directories(006_SysMets3 PUBLIC "Chapter 04 An Exercise in Text Output/01 SysMets1")

# ================================================================== Chapter 05
# -------------------------------------------------------------- 05/01 DevCaps1

add_executable(007_DevCaps1 WIN32
        "Chapter 05 Basic Drawing/01 DevCaps1/DevCaps1.c")

# -----------------------------------------------------------------------------

add_executable(008_SineWave WIN32 "Chapter 05 Basic Drawing/SineWave.c")
add_executable(009_LineDemo WIN32 "Chapter 05 Basic Drawing/LineDemo.c")
add_executable(010_Bezier WIN32 "Chapter 05 Basic Drawing/Bezier.c")
add_executable(011_AltWind WIN32 "Chapter 05 Basic Drawing/AltWind.c")
add_executable(012_WhatSize WIN32 "Chapter 05 Basic Drawing/WhatSize.c")
add_executable(013_RandRect WIN32 "Chapter 05 Basic Drawing/RandRect.c")
add_executable(014_Clover WIN32 "Chapter 05 Basic Drawing/Clover.c")

# ================================================================== Chapter 06

add_executable(015_SysMets4 WIN32 "Chapter 06 The Keyboard/SysMets4.c")
target_include_directories(015_SysMets4 PUBLIC "Chapter 04 An Exercise in Text Output/01 SysMets1")

add_executable(016_KeyView1 WIN32 "Chapter 06 The Keyboard/KeyView1.c")
add_executable(017_StokFont WIN32 "Chapter 06 The Keyboard/StokFont.c")
add_executable(018_KeyView2 WIN32 "Chapter 06 The Keyboard/KeyView2.c")
add_executable(019_Typer WIN32 "Chapter 06 The Keyboard/Typer.c")


# ================================================================== Chapter 07
add_executable(BlokOut1 WIN32 "Chapter 07 The Mouse/BlokOut1.c")
add_executable(BlokOut2 WIN32 "Chapter 07 The Mouse/BlokOut2.c")
add_executable(Checker1 WIN32 "Chapter 07 The Mouse/Checker1.c")
add_executable(Checker2 WIN32 "Chapter 07 The Mouse/Checker2.c")

# TODO: SetWindowLongPtr()
# TODO: add_executable(Checker3 WIN32 "Chapter 07 The Mouse/Checker3.c")
# TODO: add_executable(Checker4 WIN32 "Chapter 07 The Mouse/Checker4.c")

add_executable(Connect WIN32 "Chapter 07 The Mouse/Connect.c")

add_executable(SysMets WIN32 "Chapter 07 The Mouse/SysMets.c")
target_include_directories(SysMets PUBLIC "Chapter 04 An Exercise in Text Output/01 SysMets1")

add_executable(SysMets5 WIN32 "Chapter 07 The Mouse/SysMets5.c")
target_include_directories(SysMets5 PUBLIC "Chapter 04 An Exercise in Text Output/01 SysMets1")

add_executable(Beeper1 WIN32 "Chapter 08 The Timer/Beeper1.c")
add_executable(Beeper2 WIN32 "Chapter 08 The Timer/Beeper2.c")
add_executable(Clock WIN32 "Chapter 08 The Timer/Clock.c")
add_executable(DigClock WIN32 "Chapter 08 The Timer/DigClock.c")
add_executable(WhatClr WIN32 "Chapter 08 The Timer/WhatClr.c")

add_executable(BtnLook WIN32 "Chapter 09 Child Window Controls/BtnLook/BtnLook.c")

add_executable(Colors1 WIN32 "Chapter 09 Child Window Controls/Colors1/Colors1.c")
target_link_libraries(Colors1 Comctl32.lib)

add_executable(Environ WIN32 "Chapter 09 Child Window Controls/Environ/Environ.c")

add_executable(Head WIN32 "Chapter 09 Child Window Controls/Head/Head.c")
target_link_libraries(Head Comctl32.lib)

add_executable(OwnDraw WIN32 "Chapter 09 Child Window Controls/OwnDraw/OwnDraw.c")
add_executable(PopPad1 WIN32 "Chapter 09 Child Window Controls/PopPad1/PopPad1.c")
