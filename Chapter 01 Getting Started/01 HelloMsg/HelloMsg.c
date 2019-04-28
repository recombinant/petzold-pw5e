/*--------------------------------------------------------------
   HelloMsg.c -- Displays "Hello, Windows 98!" in a message box
				 (c) Charles Petzold, 1998
  --------------------------------------------------------------*/

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <tchar.h>

int WINAPI _tWinMain(
	_In_     HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_     PTSTR     pCmdLine,
	_In_     int       nShowCmd)
{
	UNREFERENCED_PARAMETER(hInstance);
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(pCmdLine);
	UNREFERENCED_PARAMETER(nShowCmd);

	// MessageBox() can only return IDOK when using MB_OK

	MessageBox(NULL, TEXT("Hello, Windows 98!"), TEXT("HelloMsg"), MB_OK);

	return 0;
}
