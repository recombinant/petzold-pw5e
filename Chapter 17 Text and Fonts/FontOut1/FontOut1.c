/*------------------------------------------
   FONTOUT1.C -- Using Path to Outline Font
                 (c) Charles Petzold, 1998
  ------------------------------------------*/

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "../EZTest/EZFont.h"

TCHAR szAppName [] = TEXT ("FontOut1") ;
TCHAR szTitle [] = TEXT ("FontOut1: Using Path to Outline Font") ;

void PaintRoutine (HWND hwnd, HDC hdc, int cxArea, int cyArea)
{
     static TCHAR szString [] = TEXT ("Outline") ;
     HFONT        hFont ;
     SIZE         size ;

     hFont = EzCreateFont (hdc, TEXT ("Times New Roman"), 1440, 0, 0, TRUE) ;

     SelectObject (hdc, hFont) ;

     GetTextExtentPoint32 (hdc, szString, lstrlen (szString), &size) ;

     BeginPath (hdc) ;
     TextOut (hdc, (cxArea - size.cx) / 2, (cyArea - size.cy) / 2,
                    szString, lstrlen (szString)) ;
     EndPath (hdc) ;

     StrokePath (hdc) ;

     SelectObject (hdc, GetStockObject (SYSTEM_FONT)) ;
     DeleteObject (hFont) ;
}
