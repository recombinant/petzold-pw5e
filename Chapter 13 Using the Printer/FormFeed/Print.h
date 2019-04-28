#pragma once
/*-------------------------------------------------------------
    PRINT.H -- Common routines for Print1, Print2, and Print3
  -------------------------------------------------------------*/

#include <windows.h>

HDC GetPrinterDC(void);            // in GetPrnDC.c
void PageGDICalls(HDC, int, int);  // in Print.c
BOOL PrintMyPage(HWND);            // in Print1.c or Print2.c or Print3.c
