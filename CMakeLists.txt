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

add_executable(007_DevCaps1 WIN32 "Chapter 05 Basic Drawing/01 DevCaps1/DevCaps1.c")
add_executable(008_SineWave WIN32 "Chapter 05 Basic Drawing/02 SineWave/SineWave.c")
add_executable(009_LineDemo WIN32 "Chapter 05 Basic Drawing/03 LineDemo/LineDemo.c")
add_executable(010_Bezier WIN32 "Chapter 05 Basic Drawing/04 Bezier/Bezier.c")
add_executable(011_AltWind WIN32 "Chapter 05 Basic Drawing/05 AltWind/AltWind.c")
add_executable(012_WhatSize WIN32 "Chapter 05 Basic Drawing/06 WhatSize/WhatSize.c")
add_executable(013_RandRect WIN32 "Chapter 05 Basic Drawing/07 RandRect/RandRect.c")
add_executable(014_Clover WIN32 "Chapter 05 Basic Drawing/08 Clover/Clover.c")

# ================================================================== Chapter 06

add_executable(015_SysMets4 WIN32 "Chapter 06 The Keyboard/01 SysMets4/SysMets4.c"
        "Chapter 04 An Exercise in Text Output/01 SysMets1/SysMets.h")
target_include_directories(015_SysMets4 PUBLIC "Chapter 04 An Exercise in Text Output/01 SysMets1")

add_executable(016_KeyView1 WIN32 "Chapter 06 The Keyboard/02 KeyView1/KeyView1.c")
add_executable(017_StokFont WIN32 "Chapter 06 The Keyboard/03 StokFont/StokFont.c")
add_executable(018_KeyView2 WIN32 "Chapter 06 The Keyboard/04 KeyView2/KeyView2.c")
add_executable(019_Typer WIN32 "Chapter 06 The Keyboard/05 Typer/Typer.c")

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

# TODO: GetWindowLongPtr()
# add_executable(Colors1 WIN32 "Chapter 09 Child Window Controls/Colors1/Colors1.c")
# target_link_libraries(Colors1 Comctl32.lib)

add_executable(Environ WIN32 "Chapter 09 Child Window Controls/Environ/Environ.c")

add_executable(Head WIN32 "Chapter 09 Child Window Controls/Head/Head.c")
target_link_libraries(Head Comctl32.lib)

add_executable(OwnDraw WIN32 "Chapter 09 Child Window Controls/OwnDraw/OwnDraw.c")
add_executable(PopPad1 WIN32 "Chapter 09 Child Window Controls/PopPad1/PopPad1.c")


add_executable(IconDemo WIN32 "Chapter 10 Menus and Other Resources/IconDemo/IconDemo.c")

# TODO: GetWindowLongPtr()
# add_executable(MenuDemo WIN32 "Chapter 10 Menus and Other Resources/MenuDemo/MenuDemo.c")
# add_executable(NoPopups WIN32 "Chapter 10 Menus and Other Resources/NoPopups/NoPopups.c")
# add_executable(PopMenu WIN32 "Chapter 10 Menus and Other Resources/PopMenu/PopMenu.c")

add_executable(PoePoem WIN32 "Chapter 10 Menus and Other Resources/PoePoem/PoePoem.c")
add_executable(PoorMenu WIN32 "Chapter 10 Menus and Other Resources/PoorMenu/PoorMenu.c")
add_executable(PopPad2 WIN32 "Chapter 10 Menus and Other Resources/PopPad2/PopPad2.c")
add_executable(About1 WIN32 "Chapter 11 Dialog Boxes/About1/About1.c")
add_executable(About2 WIN32 "Chapter 11 Dialog Boxes/About2/About2.c")
add_executable(About3 WIN32 "Chapter 11 Dialog Boxes/About3/About3.c")

# TODO: GetWindowLongPtr()
# add_executable(Colors2 WIN32 "Chapter 11 Dialog Boxes/Colors2/Colors2.c")

add_executable(Colors3 WIN32 "Chapter 11 Dialog Boxes/Colors3/Colors3.c")
add_executable(HexCalc WIN32 "Chapter 11 Dialog Boxes/HexCalc/HexCalc.c")

add_executable(PopPad WIN32 "Chapter 11 Dialog Boxes/PopPad3/PopPad.c"
        "Chapter 11 Dialog Boxes/PopPad3/PopFile.c"
        "Chapter 11 Dialog Boxes/PopPad3/PopFind.c"
        "Chapter 11 Dialog Boxes/PopPad3/PopFont.c"
        "Chapter 11 Dialog Boxes/PopPad3/PopPrntNull.c")

add_executable(ClipText WIN32 "Chapter 12 The Clipboard/ClipText/ClipText.c")
add_executable(ClipView WIN32 "Chapter 12 The Clipboard/ClipView/ClipView.c")
add_executable(DevCaps2 WIN32 "Chapter 13 Using the Printer/DevCaps2/DevCaps2.c")
add_executable(FormFeed WIN32 "Chapter 13 Using the Printer/FormFeed/FormFeed.c"
        "Chapter 13 Using the Printer/FormFeed/GetPrnDC.c")

add_executable(PopPrnt WIN32 "Chapter 11 Dialog Boxes/PopPad3/PopPad.c"
        "Chapter 11 Dialog Boxes/PopPad3/PopFile.c"
        "Chapter 11 Dialog Boxes/PopPad3/PopFind.c"
        "Chapter 11 Dialog Boxes/PopPad3/PopFont.c"
        "Chapter 13 Using the Printer/PopPad/PopPrnt.c")

add_executable(Print1 WIN32 "Chapter 13 Using the Printer/Print1/Print1.c"
        "Chapter 13 Using the Printer/Print1/Print.c"
        "Chapter 13 Using the Printer/FormFeed/GetPrnDC.c")
add_executable(Print2 WIN32 "Chapter 13 Using the Printer/Print2/Print2.c"
        "Chapter 13 Using the Printer/Print1/Print.c"
        "Chapter 13 Using the Printer/FormFeed/GetPrnDC.c")
add_executable(Print3 WIN32 "Chapter 13 Using the Printer/Print3/Print3.c"
        "Chapter 13 Using the Printer/Print1/Print.c"
        "Chapter 13 Using the Printer/FormFeed/GetPrnDC.c")
add_executable(BitBlt WIN32 "Chapter 14 Bitmaps and Bitblts/BitBlt/BitBlt.c")
add_executable(BitMask WIN32 "Chapter 14 Bitmaps and Bitblts/BitMask/BitMask.c")
add_executable(Blowup WIN32 "Chapter 14 Bitmaps and Bitblts/Blowup/Blowup.c")
add_executable(Bounce1 WIN32 "Chapter 14 Bitmaps and Bitblts/Bounce1/Bounce1.c")
add_executable(Bricks1 WIN32 "Chapter 14 Bitmaps and Bitblts/Bricks1/Bricks1.c")
add_executable(Bricks2 WIN32 "Chapter 14 Bitmaps and Bitblts/Bricks2/Bricks2.c")
add_executable(Bricks3 WIN32 "Chapter 14 Bitmaps and Bitblts/Bricks3/Bricks3.c")
add_executable(GrafMenu WIN32 "Chapter 14 Bitmaps and Bitblts/GrafMenu/GrafMenu.c")
add_executable(HelloBit WIN32 "Chapter 14 Bitmaps and Bitblts/HelloBit/HelloBit.c")
add_executable(Scramble WIN32 "Chapter 14 Bitmaps and Bitblts/Scramble/Scramble.c")
add_executable(Sketch WIN32 "Chapter 14 Bitmaps and Bitblts/Sketch/Sketch.c")
add_executable(Stretch WIN32 "Chapter 14 Bitmaps and Bitblts/Stretch/Stretch.c")

add_executable(Apollo11 WIN32 "Chapter 15 The Device Independent Bitmap/Apollo11/Apollo11.c"
        "Chapter 15 The Device Independent Bitmap/ShowDib1/DibFile.c")
target_include_directories(Apollo11 PUBLIC "Chapter 15 The Device Independent Bitmap/ShowDib1")

add_executable(DibConv WIN32 "Chapter 15 The Device Independent Bitmap/DibConv/DibConv.c")
add_executable(DibHeads WIN32 "Chapter 15 The Device Independent Bitmap/DibHeads/DibHeads.c")
add_executable(DibSect WIN32 "Chapter 15 The Device Independent Bitmap/DibSect/DibSect.c")
add_executable(SeqDisp WIN32 "Chapter 15 The Device Independent Bitmap/SeqDisp/SeqDisp.c")

add_executable(ShowDib1 WIN32 "Chapter 15 The Device Independent Bitmap/ShowDib1/ShowDib1.c"
        "Chapter 15 The Device Independent Bitmap/ShowDib1/DibFile.c")

add_executable(ShowDib2 WIN32 "Chapter 15 The Device Independent Bitmap/ShowDib2/Showdib2.c"
        "Chapter 15 The Device Independent Bitmap/ShowDib1/DibFile.c")
target_include_directories(ShowDib2 PUBLIC "Chapter 15 The Device Independent Bitmap/ShowDib1")

# TODO: "Chapter 16 The Palette Manager/AllColor/AllColor.c"
add_executable(Bounce2 WIN32 "Chapter 16 The Palette Manager/Bounce2/Bounce2.c"
        "Chapter 16 The Palette Manager/Bounce2/PalAnim.c")
add_executable(Dibble WIN32 "Chapter 16 The Palette Manager/Dibble/Dibble.c"
        "Chapter 16 The Palette Manager/Dibble/DibHelp.c"
        "Chapter 16 The Palette Manager/Dibble/DibConv.c"
        "Chapter 16 The Palette Manager/Dibble/DibPal.c")
# TODO: "Chapter 16 The Palette Manager/Fader/Fader.c"
add_executable(Grays1 WIN32 "Chapter 16 The Palette Manager/Grays1/Grays1.c")
add_executable(Grays2 WIN32 "Chapter 16 The Palette Manager/Grays2/Grays2.c")
add_executable(Grays3 WIN32 "Chapter 16 The Palette Manager/Grays3/Grays3.c")
# TODO: "Chapter 16 The Palette Manager/Pipes/Pipes.c"

add_executable(ShowDib3 WIN32 "Chapter 16 The Palette Manager/ShowDib3/ShowDib3.c"
        "Chapter 16 The Palette Manager/ShowDib3/PackeDib.c")

add_executable(ShowDib4 WIN32 "Chapter 16 The Palette Manager/ShowDib4/ShowDib4.c"
        "Chapter 16 The Palette Manager/ShowDib3/PackeDib.c")
target_include_directories(ShowDib4 PUBLIC "Chapter 16 The Palette Manager/ShowDib3")

add_executable(ShowDib5 WIN32 "Chapter 16 The Palette Manager/ShowDib5/ShowDib5.c"
        "Chapter 16 The Palette Manager/ShowDib3/PackeDib.c")
target_include_directories(ShowDib5 PUBLIC "Chapter 16 The Palette Manager/ShowDib3")

add_executable(ShowDib6 WIN32 "Chapter 16 The Palette Manager/ShowDib6/ShowDib6.c"
        "Chapter 16 The Palette Manager/ShowDib3/PackeDib.c")
target_include_directories(ShowDib6 PUBLIC "Chapter 16 The Palette Manager/ShowDib3")

add_executable(ShowDib7 WIN32 "Chapter 16 The Palette Manager/ShowDib7/ShowDib7.c"
        "Chapter 16 The Palette Manager/ShowDib3/PackeDib.c")
target_include_directories(ShowDib7 PUBLIC "Chapter 16 The Palette Manager/ShowDib3")

add_executable(ShowDib8 WIN32 "Chapter 16 The Palette Manager/ShowDib8/ShowDib8.c"
        "Chapter 16 The Palette Manager/ShowDib3/PackeDib.c")
target_include_directories(ShowDib8 PUBLIC "Chapter 16 The Palette Manager/ShowDib3")

add_executable(SysPal1 WIN32 "Chapter 16 The Palette Manager/SysPal1/SysPal1.c")
add_executable(SysPal2 WIN32 "Chapter 16 The Palette Manager/SysPal2/SysPal2.c")
add_executable(SysPal3 WIN32 "Chapter 16 The Palette Manager/SysPal3/SysPal3.c")
# TODO: "Chapter 16 The Palette Manager/Tunnel/Tunnel.c"
add_executable(ChosFont WIN32 "Chapter 17 Text and Fonts/ChosFont/ChosFont.c")
add_executable(EndJoin WIN32 "Chapter 17 Text and Fonts/EndJoin/EndJoin.c")

add_executable(EZTest WIN32 "Chapter 17 Text and Fonts/EZTest/EZTest.c"
        "Chapter 17 Text and Fonts/EZTest/FontDemo.c"
        "Chapter 17 Text and Fonts/EZTest/EZFont.c"
        "Chapter 17 Text and Fonts/EZTest/EZFont.h")

add_executable(FontClip WIN32 "Chapter 17 Text and Fonts/FontClip/FontClip.c"
        "Chapter 17 Text and Fonts/EZTest/FontDemo.c"
        "Chapter 17 Text and Fonts/EZTest/EZFont.c"
        "Chapter 17 Text and Fonts/EZTest/EZFont.h")
target_include_directories(FontClip PUBLIC "Chapter 17 Text and Fonts/EZTest")

add_executable(FontFill WIN32 "Chapter 17 Text and Fonts/FontFill/FontFill.c"
        "Chapter 17 Text and Fonts/EZTest/FontDemo.c"
        "Chapter 17 Text and Fonts/EZTest/EZFont.c"
        "Chapter 17 Text and Fonts/EZTest/EZFont.h")
target_include_directories(FontFill PUBLIC "Chapter 17 Text and Fonts/EZTest")

add_executable(FontOut1 WIN32 "Chapter 17 Text and Fonts/FontOut1/FontOut1.c"
        "Chapter 17 Text and Fonts/EZTest/FontDemo.c"
        "Chapter 17 Text and Fonts/EZTest/EZFont.c"
        "Chapter 17 Text and Fonts/EZTest/EZFont.h")
target_include_directories(FontOut1 PUBLIC "Chapter 17 Text and Fonts/EZTest")

add_executable(FontOut2 WIN32 "Chapter 17 Text and Fonts/FontOut2/FontOut2.c"
        "Chapter 17 Text and Fonts/EZTest/FontDemo.c"
        "Chapter 17 Text and Fonts/EZTest/EZFont.c"
        "Chapter 17 Text and Fonts/EZTest/EZFont.h")
target_include_directories(FontOut2 PUBLIC "Chapter 17 Text and Fonts/EZTest")

add_executable(FontRot WIN32 "Chapter 17 Text and Fonts/FontRot/FontRot.c"
        "Chapter 17 Text and Fonts/EZTest/FontDemo.c"
        "Chapter 17 Text and Fonts/EZTest/EZFont.c"
        "Chapter 17 Text and Fonts/EZTest/EZFont.h")

add_executable(Justify1 WIN32 "Chapter 17 Text and Fonts/Justify1/Justify1.c")
add_executable(Justify2 WIN32 "Chapter 17 Text and Fonts/Justify2/Justify2.c")
add_executable(PickFont WIN32 "Chapter 17 Text and Fonts/PickFont/PickFont.c")
add_executable(Unichars WIN32 "Chapter 17 Text and Fonts/UniChars/Unichars.c")
add_executable(Emf01 WIN32 "Chapter 18 Metafiles/Emf01/Emf01.c")
add_executable(Emf02 WIN32 "Chapter 18 Metafiles/Emf02/Emf02.c")
add_executable(Emf03 WIN32 "Chapter 18 Metafiles/Emf03/Emf03.c")
add_executable(Emf04 WIN32 "Chapter 18 Metafiles/Emf04/Emf04.c")
add_executable(Emf05 WIN32 "Chapter 18 Metafiles/Emf05/Emf05.c")
add_executable(Emf06 WIN32 "Chapter 18 Metafiles/Emf06/Emf06.c")
add_executable(Emf07 WIN32 "Chapter 18 Metafiles/Emf07/Emf07.c")

add_executable(Emf08 WIN32 "Chapter 18 Metafiles/Emf08/Emf08.c"
        "Chapter 18 Metafiles/Emf08/Emf.c")
target_include_directories(Emf08 PUBLIC "Chapter 18 Metafiles/Emf08")

add_executable(Emf09 WIN32 "Chapter 18 Metafiles/Emf09/Emf09.c"
        "Chapter 18 Metafiles/Emf08/Emf.c")
target_include_directories(Emf09 PUBLIC "Chapter 18 Metafiles/Emf08")

add_executable(Emf10 WIN32 "Chapter 18 Metafiles/Emf10/Emf10.c"
        "Chapter 18 Metafiles/Emf08/Emf.c")
target_include_directories(Emf10 PUBLIC "Chapter 18 Metafiles/Emf08")

add_executable(Emf11 WIN32 "Chapter 18 Metafiles/Emf11/Emf11.c"
        "Chapter 18 Metafiles/Emf08/Emf.c")
target_include_directories(Emf11 PUBLIC "Chapter 18 Metafiles/Emf08")

add_executable(Emf12 WIN32 "Chapter 18 Metafiles/Emf12/Emf12.c"
        "Chapter 18 Metafiles/Emf08/Emf.c")
target_include_directories(Emf12 PUBLIC "Chapter 18 Metafiles/Emf08")

add_executable(Emf13 WIN32 "Chapter 18 Metafiles/Emf13/Emf13.c"
        "Chapter 18 Metafiles/Emf08/Emf.c")
target_include_directories(Emf13 PUBLIC "Chapter 18 Metafiles/Emf08")

add_executable(EmfView WIN32 "Chapter 18 Metafiles/EmfView/EmfView.c")
add_executable(Metafile WIN32 "Chapter 18 Metafiles/MetaFile/Metafile.c")

add_executable(MDIDemo WIN32 "Chapter 19 The Multiple-Document Interface/MDIDemo/MDIDemo.c")

add_executable(BigJob1 WIN32 "Chapter 20 Multitasking and Multithreading/BigJob1/BigJob1.c")
add_executable(BigJob2 WIN32 "Chapter 20 Multitasking and Multithreading/BigJob2/BigJob2.c")

# TODO: GetWindowLong()
# add_executable(Multi1 WIN32 "Chapter 20 Multitasking and Multithreading/Multi1/Multi1.c")
# add_executable(Multi2 WIN32 "Chapter 20 Multitasking and Multithreading/Multi2/Multi2.c")

add_executable(RndRctMT WIN32 "Chapter 20 Multitasking and Multithreading/RndRectMT/RndRctMT.c")
add_executable(EdrTest WIN32 "Chapter 21 Dynamic-Link Libraries/EdrTest/EdrTest.c"
        "Chapter 21 Dynamic-Link Libraries/EdrTest/EdrLib.c")
add_executable(ShowBit WIN32 "Chapter 21 Dynamic-Link Libraries/ShowBit/ShowBit.c"
        "Chapter 21 Dynamic-Link Libraries/ShowBit/BitLib.c")
add_executable(StrProg WIN32 "Chapter 21 Dynamic-Link Libraries/StrProg/StrProg.c"
        "Chapter 21 Dynamic-Link Libraries/StrProg/StrLib.c")
add_executable(AddSynth WIN32 "Chapter 22 Sound and Music/AddSynth/AddSynth.c")
target_link_libraries(AddSynth winmm.lib)

add_executable(BachTocc WIN32 "Chapter 22 Sound and Music/BachTocc/BachTocc.c")
target_link_libraries(BachTocc winmm.lib)

add_executable(Drum WIN32 "Chapter 22 Sound and Music/Drum/Drum.c"
        "Chapter 22 Sound and Music/Drum/DrumFile.c"
        "Chapter 22 Sound and Music/Drum/DrumTime.c")
target_link_libraries(Drum winmm.lib)

add_executable(KBMidi WIN32 "Chapter 22 Sound and Music/KBMidi/KBMidi.c")
target_link_libraries(KBMidi winmm.lib)

add_executable(Record1 WIN32 "Chapter 22 Sound and Music/Record1/Record1.c")
target_link_libraries(Record1 winmm.lib)

add_executable(Record2 WIN32 "Chapter 22 Sound and Music/Record2/Record2.c")
target_include_directories(Record2 PUBLIC "Chapter 22 Sound and Music/Record1/")
target_link_libraries(Record2 winmm.lib)

add_executable(Record3 WIN32 "Chapter 22 Sound and Music/Record3/Record3.c")
target_include_directories(Record3 PUBLIC "Chapter 22 Sound and Music/Record1/")
target_link_libraries(Record3 winmm.lib)

add_executable(SineWaveGen WIN32 "Chapter 22 Sound and Music/SineWaveGen/SineWaveGen.c")
target_link_libraries(SineWaveGen winmm.lib)

add_executable(TestMci WIN32 "Chapter 22 Sound and Music/TextMCI/TestMci.c")
target_link_libraries(TestMci winmm.lib)

# TODO: GetWindowLong()
# add_executable(WakeUp WIN32 "Chapter 22 Sound and Music/WakeUp/WakeUp.c")

add_executable(NetTime WIN32 "Chapter 23 A Taste of the Internet/NetTime/NetTime.c")
target_link_libraries(NetTime Ws2_32.lib)

add_executable(UpdDemo WIN32 "Chapter 23 A Taste of the Internet/UpdDemo/UpdDemo.c ")
target_link_libraries(UpdDemo Wininet.lib)
