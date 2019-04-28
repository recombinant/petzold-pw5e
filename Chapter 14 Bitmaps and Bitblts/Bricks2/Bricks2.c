/*-----------------------------------------
   BRICKS2.C -- CreateBitmap Demonstration
				(c) Charles Petzold, 1998
  -----------------------------------------*/

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <windowsx.h>
#include <tchar.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI _tWinMain(
	_In_     HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_     PTSTR     pCmdLine,
	_In_     int       nShowCmd)
{
	static TCHAR szAppName[] = TEXT("Bricks2");
	HWND         hwnd;
	MSG          msg;
	WNDCLASS     wndclass;

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

	hwnd = CreateWindow(szAppName, TEXT("CreateBitmap Demo"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, NULL, hInstance, NULL);

	ShowWindow(hwnd, nShowCmd);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int)msg.wParam;  // WM_QUIT
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static BITMAP  bitmap = { 0, 8, 8, 2, 1, 1 };
	static BYTE    bits[8][2] = { 0xFF, 0, 0x0C, 0, 0x0C, 0, 0x0C, 0,
								   0xFF, 0, 0xC0, 0, 0xC0, 0, 0xC0, 0 };
	static HBITMAP hBitmap;
	static int     cxClient, cyClient, cxSource, cySource;
	HDC            hdc, hdcMem;
	int            x, y;
	PAINTSTRUCT    ps;

	switch (message)
	{
	case WM_CREATE:
		bitmap.bmBits = bits;
		hBitmap = CreateBitmapIndirect(&bitmap);
		cxSource = bitmap.bmWidth;
		cySource = bitmap.bmHeight;
		return 0;

	case WM_SIZE:
		cxClient = GET_X_LPARAM(lParam);
		cyClient = GET_Y_LPARAM(lParam);
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		hdcMem = CreateCompatibleDC(hdc);
		SelectObject(hdcMem, hBitmap);

		for (y = 0; y < cyClient; y += cySource)
			for (x = 0; x < cxClient; x += cxSource)
			{
				BitBlt(hdc, x, y, cxSource, cySource, hdcMem, 0, 0, SRCCOPY);
			}

		DeleteDC(hdcMem);
		EndPaint(hwnd, &ps);
		return 0;

	case WM_DESTROY:
		DeleteObject(hBitmap);
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}
