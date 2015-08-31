/*--------------------------------------------------------------
   HelloMsg.c -- Displays "Hello, Windows 98!" in a message box
                 (c) Charles Petzold, 1998
  --------------------------------------------------------------*/

#include <windows.h>
#include <tchar.h>

int WINAPI _tWinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ PTSTR lpCmdLine,
	_In_ int nShowCmd)
{
        // MessageBox() can only return IDOK when using MB_OK

    MessageBox(NULL, TEXT("Hello, Windows 98!"), TEXT("HelloMsg"), MB_OK);

    return 0;
}
