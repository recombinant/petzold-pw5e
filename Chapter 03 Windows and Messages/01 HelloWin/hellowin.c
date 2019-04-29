/*------------------------------------------------------------
   HelloWin.c -- Displays "Hello, Windows 98!" in client area
				 (c) Charles Petzold, 1998
  ------------------------------------------------------------*/

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <windowsx.h>
#include <tchar.h>
#include <stdlib.h>
#include <mmsystem.h>

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI _tWinMain(
	_In_     HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_     PTSTR     pCmdLine,
	_In_     int       nShowCmd)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(pCmdLine);

	static TCHAR app_name[] = TEXT("HelloWin");
	WNDCLASSEX   wndclassex;

	ZeroMemory(&wndclassex, sizeof(wndclassex));
	wndclassex.cbSize = sizeof(wndclassex);
	wndclassex.style = CS_HREDRAW | CS_VREDRAW;
	wndclassex.lpfnWndProc = WndProc;
	//wndclassex.cbClsExtra = 0;
	//wndclassex.cbWndExtra = 0;
	wndclassex.hInstance = hInstance;
	wndclassex.hIcon = LoadImage(
		hInstance,        // hInst
		IDI_APPLICATION,  // name
		IMAGE_ICON,       // type
		0,                // cx
		0,                // cy
		LR_SHARED);       // fuLoad
	wndclassex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclassex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclassex.hbrBackground = GetStockBrush(WHITE_BRUSH);
	//wndclassex.lpszMenuName = NULL;
	wndclassex.lpszClassName = app_name;
	//wndclassex.hIconSm = NULL;

	ATOM atom = RegisterClassEx(&wndclassex);
	if (0 == atom)
	{
		return 0;  // premature exit
	}

	HWND hwnd = CreateWindow(
		(PCTSTR)atom,               // window class name or atom
		TEXT("The Hello Program"),  // window caption
		WS_OVERLAPPEDWINDOW,        // window style
		CW_USEDEFAULT,              // initial x position
		CW_USEDEFAULT,              // initial y position
		CW_USEDEFAULT,              // initial x size
		CW_USEDEFAULT,              // initial y size
		NULL,                       // parent window handle
		NULL,                       // window menu handle
		hInstance,                  // program instance handle
		NULL);                      // creation parameters
	if (0 == hwnd)
	{
		return 0;  // premature exit
	}

	ShowWindow(hwnd, nShowCmd);
	if (0 == UpdateWindow(hwnd))
	{
		return 0;  // premature exit
	}

	MSG  msg;
	BOOL ret;  // three states: -1, 0 or non-zero

	while (0 != (ret = GetMessage(&msg, NULL, 0, 0)))
	{
		if (-1 == ret)
		{
			// handle the error and/or exit
			// for error call GetLastError();
			return 0;
		}
		else
		{
			TranslateMessage(&msg);
			(void)DispatchMessage(&msg);
		}
	}
	return (int)msg.wParam;  // WM_QUIT
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
		(void)PlaySound(TEXT("hellowin.wav"), NULL, SND_FILENAME | SND_ASYNC);
		return 0;  // message processed

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);

		RECT rect;
		(void)GetClientRect(hwnd, &rect);

		(void)DrawText(hdc, TEXT("Hello, Windows 98!"), -1, &rect,
			DT_SINGLELINE | DT_CENTER | DT_VCENTER);

		(void)EndPaint(hwnd, &ps);
	}
	return 0;  // message processed

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;  // message processed

	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}
}
