/*--------------------------------------------------------------
   HelloMsg.c -- Displays "Hello, Windows 98!" in a message box
                 (c) Charles Petzold, 1998
  --------------------------------------------------------------*/

#include <windows.h>

int CALLBACK WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nShowCmd
	)
{
    MessageBox(NULL, TEXT("Hello, Windows 98!"), TEXT("HelloMsg"), 0);

    return 0;
}
