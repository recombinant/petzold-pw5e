#pragma once
/*---------------------------------------
	POPPAD.H -- Popup Editor
	(c) Charles Petzold, 1998
  ---------------------------------------*/

#include <windows.h>
#include <commdlg.h>

  // Functions in POPFILE.C

void PopFileInitialize(HWND);
BOOL PopFileOpenDlg(HWND, PTSTR, PTSTR);
BOOL PopFileSaveDlg(HWND, PTSTR, PTSTR);
BOOL PopFileRead(HWND, PTSTR);
BOOL PopFileWrite(HWND, PTSTR);

// Functions in POPFIND.C

HWND PopFindFindDlg(HWND);
HWND PopFindReplaceDlg(HWND);
BOOL PopFindFindText(HWND, int*, LPFINDREPLACE);
BOOL PopFindReplaceText(HWND, int*, LPFINDREPLACE);
BOOL PopFindNextText(HWND, int*);
BOOL PopFindValidFind(void);

// Functions in POPFONT.C

void PopFontInitialize(HWND);
BOOL PopFontChooseFont(HWND);
void PopFontSetFont(HWND);
void PopFontDeinitialize(void);

// Functions in POPPRNT.C

BOOL PopPrntPrintFile(HINSTANCE, HWND, HWND, PTSTR);
