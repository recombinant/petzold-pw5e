/*-------------------------------------------
   POEPOEM.C -- Demonstrates Custom Resource
				(c) Charles Petzold, 1998
  -------------------------------------------*/

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <windowsx.h>
#include <tchar.h>
#include <stdlib.h>
#include "Resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE hInst;

int WINAPI _tWinMain(
	_In_     HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_     PTSTR     pCmdLine,
	_In_     int       nShowCmd)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(pCmdLine);

	TCHAR    szAppName[16], szCaption[64], szErrMsg[64];
	HWND     hwnd;
	MSG      msg;
	WNDCLASS wndclass;

	LoadString(hInstance, IDS_APPNAME, szAppName, _countof(szAppName));

	LoadString(hInstance, IDS_CAPTION, szCaption, _countof(szCaption));

	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(hInstance, szAppName);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;
	
	hInst = hInstance;
	
	if (!RegisterClass(&wndclass))
	{
		LoadStringA(hInstance, IDS_APPNAME, (char*)szAppName, sizeof(szAppName));

		LoadStringA(hInstance, IDS_ERRMSG, (char*)szErrMsg, sizeof(szErrMsg));

		MessageBoxA(NULL, (char*)szErrMsg, (char*)szAppName, MB_ICONERROR);
		return 0;
	}

	hwnd = CreateWindow(szAppName, szCaption,
		WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
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
	static char* pText;
        static char* pRsc, * pWorking;
	static DWORD fileSize = 0;
	static HGLOBAL hResource;
	static HWND    hScroll;
	static int     iPosition, cxChar, cyChar, cyClient, iNumLines, xScroll;
	HDC            hdc;
	PAINTSTRUCT    ps;
	RECT           rect;
	TEXTMETRIC     tm;

	switch (message)
	{
	case WM_CREATE:
		hdc = GetDC(hwnd);
		GetTextMetrics(hdc, &tm);
		cxChar = tm.tmAveCharWidth;
		cyChar = tm.tmHeight + tm.tmExternalLeading;
		ReleaseDC(hwnd, hdc);

		xScroll = GetSystemMetrics(SM_CXVSCROLL);

		hScroll = CreateWindow(TEXT("scrollbar"), NULL,
			WS_CHILD | WS_VISIBLE | SBS_VERT,
			0, 0, 0, 0,
			hwnd, (HMENU)1, hInst, NULL);

		HRSRC rc = FindResource(hInst, TEXT("ANNABELLEE"), TEXT("TEXT"));
		if (rc)
		{
			hResource = LoadResource(hInst, rc);
			fileSize = SizeofResource(hInst, rc);
			if (hResource) pText = LockResource(hResource);
		}	
		pRsc = malloc(sizeof(TCHAR) * fileSize);
		if (pRsc) memcpy(pRsc, pText, fileSize);
		pWorking = pRsc;
			
		/*hResource = LoadResource(
			hInst,
			FindResource(hInst, TEXT("AnnabelLee"), TEXT("TEXT")));*/

		//pText = (char*)LockResource(hResource);
		iNumLines = 0;

		if (pWorking)
		{
			while (*pWorking != '\\' && *pWorking != '\0')
			{
				if (*pWorking == '\n')
					iNumLines++;
				pWorking = AnsiNext(pWorking);
			}
			*pWorking = '\0';
		}

		SetScrollRange(hScroll, SB_CTL, 0, iNumLines, FALSE);
		SetScrollPos(hScroll, SB_CTL, 0, FALSE);
		return 0;

	case WM_SIZE:
		MoveWindow(hScroll, GET_X_LPARAM(lParam) - xScroll, 0,
			xScroll, cyClient = GET_Y_LPARAM(lParam), TRUE);
		SetFocus(hwnd);
		return 0;

	case WM_SETFOCUS:
		SetFocus(hScroll);
		return 0;

	case WM_VSCROLL:
		switch (wParam)
		{
		case SB_TOP:
			iPosition = 0;
			break;
		case SB_BOTTOM:
			iPosition = iNumLines;
			break;
		case SB_LINEUP:
			iPosition -= 1;
			break;
		case SB_LINEDOWN:
			iPosition += 1;
			break;
		case SB_PAGEUP:
			iPosition -= cyClient / cyChar;
			break;
		case SB_PAGEDOWN:
			iPosition += cyClient / cyChar;
			break;
		case SB_THUMBPOSITION:
			iPosition = LOWORD(lParam);
			break;
		}
		iPosition = max(0, min(iPosition, iNumLines));

		if (iPosition != GetScrollPos(hScroll, SB_CTL))
		{
			SetScrollPos(hScroll, SB_CTL, iPosition, TRUE);
			InvalidateRect(hwnd, NULL, TRUE);
		}
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		//pText = (char*)LockResource(hResource);

		GetClientRect(hwnd, &rect);
		rect.left += cxChar;
		rect.top += cyChar * (1 - iPosition);
		DrawTextA(hdc, pRsc, -1, &rect, DT_EXTERNALLEADING);

		EndPaint(hwnd, &ps);
		return 0;

	case WM_DESTROY:
		FreeResource(hResource);
		free(pRsc);
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}
