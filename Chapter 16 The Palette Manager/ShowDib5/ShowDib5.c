/*--------------------------------------------------
   SHOWDIB5.C -- Displays DIB with halftone palette
				 (c) Charles Petzold, 1998
  --------------------------------------------------*/

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <windowsx.h>
#include <tchar.h>
#include <commdlg.h>
#include <malloc.h>
#include "../ShowDib3/PackeDib.h"
#include "Resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

TCHAR szAppName[] = TEXT("ShowDib5");

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
	wndclass.lpszMenuName = szAppName;
	wndclass.lpszClassName = szAppName;

	if (!RegisterClass(&wndclass))
	{
		MessageBox(NULL, TEXT("This program requires Windows NT!"),
			szAppName, MB_ICONERROR);
		return 0;
	}

	hwnd = CreateWindow(szAppName, TEXT("Show DIB #5: Halftone Palette"),
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
	static BITMAPINFO* pPackedDib;
	static HPALETTE     hPalette;
	static int          cxClient, cyClient;
	static OPENFILENAME ofn;
	static TCHAR        szFileName[MAX_PATH], szTitleName[MAX_PATH];
	static TCHAR        szFilter[] = TEXT("Bitmap Files (*.BMP)\0*.bmp\0")
		TEXT("All Files (*.*)\0*.*\0\0");
	HDC                 hdc;
	PAINTSTRUCT         ps;

	switch (message)
	{
	case WM_CREATE:
		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.hwndOwner = hwnd;
		ofn.hInstance = NULL;
		ofn.lpstrFilter = szFilter;
		ofn.lpstrCustomFilter = NULL;
		ofn.nMaxCustFilter = 0;
		ofn.nFilterIndex = 0;
		ofn.lpstrFile = szFileName;
		ofn.nMaxFile = MAX_PATH;
		ofn.lpstrFileTitle = szTitleName;
		ofn.nMaxFileTitle = MAX_PATH;
		ofn.lpstrInitialDir = NULL;
		ofn.lpstrTitle = NULL;
		ofn.Flags = 0;
		ofn.nFileOffset = 0;
		ofn.nFileExtension = 0;
		ofn.lpstrDefExt = TEXT("bmp");
		ofn.lCustData = 0;
		ofn.lpfnHook = NULL;
		ofn.lpTemplateName = NULL;

		// Create the All-Purpose Palette

		hdc = GetDC(hwnd);
		hPalette = CreateHalftonePalette(hdc);
		ReleaseDC(hwnd, hdc);
		return 0;

	case WM_SIZE:
		cxClient = GET_X_LPARAM(lParam);
		cyClient = GET_Y_LPARAM(lParam);
		return 0;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDM_FILE_OPEN:

			// Show the File Open dialog box

			if (!GetOpenFileName(&ofn))
				return 0;

			// If there's an existing packed DIB, free the memory

			if (pPackedDib)
			{
				free(pPackedDib);
				pPackedDib = NULL;
			}

			// Load the packed DIB into memory

			SetCursor(LoadCursor(NULL, IDC_WAIT));
			ShowCursor(TRUE);

			pPackedDib = PackedDibLoad(szFileName);

			ShowCursor(FALSE);
			SetCursor(LoadCursor(NULL, IDC_ARROW));

			if (!pPackedDib)
			{
				MessageBox(hwnd, TEXT("Cannot load DIB file"),
					szAppName, 0);
			}
			InvalidateRect(hwnd, NULL, TRUE);
			return 0;
		}
		break;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		if (pPackedDib)
		{
			// Set halftone stretch mode

			SetStretchBltMode(hdc, HALFTONE);
			SetBrushOrgEx(hdc, 0, 0, NULL);

			// Select and realize halftone palette

			SelectPalette(hdc, hPalette, FALSE);
			RealizePalette(hdc);

			// StretchDIBits rather than SetDIBitsToDevice

			StretchDIBits(hdc,
				0,
				0,
				PackedDibGetWidth(pPackedDib),
				PackedDibGetHeight(pPackedDib),
				0,
				0,
				PackedDibGetWidth(pPackedDib),
				PackedDibGetHeight(pPackedDib),
				PackedDibGetBitsPtr(pPackedDib),
				pPackedDib,
				DIB_RGB_COLORS,
				SRCCOPY);
		}
		EndPaint(hwnd, &ps);
		return 0;

	case WM_QUERYNEWPALETTE:
		hdc = GetDC(hwnd);
		SelectPalette(hdc, hPalette, FALSE);
		RealizePalette(hdc);
		InvalidateRect(hwnd, NULL, TRUE);

		ReleaseDC(hwnd, hdc);
		return TRUE;

	case WM_PALETTECHANGED:
		if ((HWND)wParam != hwnd)

			hdc = GetDC(hwnd);
		SelectPalette(hdc, hPalette, FALSE);
		RealizePalette(hdc);
		UpdateColors(hdc);

		ReleaseDC(hwnd, hdc);
		break;

	case WM_DESTROY:
		if (pPackedDib)
			free(pPackedDib);

		DeleteObject(hPalette);

		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}
