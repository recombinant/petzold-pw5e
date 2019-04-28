/*----------------------------------------
   SYSPAL1.C -- Displays system palette
				(c) Charles Petzold, 1998
  ----------------------------------------*/

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <windowsx.h>
#include <tchar.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

TCHAR szAppName[] = TEXT("SysPal1");

int WINAPI _tWinMain(
	_In_     HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_     PTSTR     pCmdLine,
	_In_     int       nShowCmd)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(pCmdLine);

	HWND     hwnd;
	MSG      msg;
	WNDCLASS wndclass;

	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;

	if (!RegisterClass(&wndclass))
	{
		MessageBox(NULL, TEXT("This program requires Windows NT!"),
			szAppName, MB_ICONERROR);
		return 0;
	}

	hwnd = CreateWindow(szAppName, TEXT("System Palette #1"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, NULL, hInstance, NULL);

	if (!hwnd)
		return 0;

	ShowWindow(hwnd, nShowCmd);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int)msg.wParam;  // WM_QUIT
}

BOOL CheckDisplay(HWND hwnd)
{
	HDC hdc;
	int iPalSize;

	hdc = GetDC(hwnd);
	iPalSize = GetDeviceCaps(hdc, SIZEPALETTE);
	ReleaseDC(hwnd, hdc);

	if (iPalSize != 256)
	{
		MessageBox(hwnd, TEXT("This program requires that the video ")
			TEXT("display mode have a 256-color palette."),
			szAppName, MB_ICONERROR);
		return FALSE;
	}
	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static int   cxClient, cyClient;
	static SIZE  sizeChar;
	HDC          hdc;
	int          i, x, y;
	PAINTSTRUCT  ps;
	PALETTEENTRY pe[256];
	TCHAR        szBuffer[16];

	switch (message)
	{
	case WM_CREATE:
		if (!CheckDisplay(hwnd))
			return -1;

		hdc = GetDC(hwnd);
		SelectObject(hdc, GetStockObject(SYSTEM_FIXED_FONT));
		GetTextExtentPoint32(hdc, TEXT("FF-FF-FF"), 10, &sizeChar);
		ReleaseDC(hwnd, hdc);
		return 0;

	case WM_DISPLAYCHANGE:
		if (!CheckDisplay(hwnd))
			DestroyWindow(hwnd);

		return 0;

	case WM_SIZE:
		cxClient = GET_X_LPARAM(lParam);
		cyClient = GET_Y_LPARAM(lParam);
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		SelectObject(hdc, GetStockObject(SYSTEM_FIXED_FONT));

		GetSystemPaletteEntries(hdc, 0, 256, pe);

		for (i = 0, x = 0, y = 0; i < 256; i++)
		{
			wsprintf(szBuffer, TEXT("%02X-%02X-%02X"),
				pe[i].peRed, pe[i].peGreen, pe[i].peBlue);

			TextOut(hdc, x, y, szBuffer, lstrlen(szBuffer));

			if ((x += sizeChar.cx) + sizeChar.cx > cxClient)
			{
				x = 0;

				if ((y += sizeChar.cy) > cyClient)
					break;
			}
		}
		EndPaint(hwnd, &ps);
		return 0;

	case WM_PALETTECHANGED:
		InvalidateRect(hwnd, NULL, FALSE);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}
