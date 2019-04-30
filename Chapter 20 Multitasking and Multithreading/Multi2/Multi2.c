/*---------------------------------------
   MULTI2.C -- Multitasking Demo
			   (c) Charles Petzold, 1998
  ---------------------------------------*/

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <windowsx.h>
#include <tchar.h>
#include <math.h>
#include <process.h>

typedef struct
{
	HWND hwnd;
	int  cxClient;
	int  cyClient;
	int  cyChar;
	BOOL bKill;
}
PARAMS, * PPARAMS;

LRESULT APIENTRY WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI _tWinMain(
	_In_     HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_     PTSTR     pCmdLine,
	_In_     int       nShowCmd)
{
	static TCHAR szAppName[] = TEXT("Multi2");
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

	hwnd = CreateWindow(szAppName, TEXT("Multitasking Demo"),
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

int CheckBottom(HWND hwnd, int cyClient, int cyChar, int iLine)
{
	if (iLine * cyChar + cyChar > cyClient)
	{
		InvalidateRect(hwnd, NULL, TRUE);
		UpdateWindow(hwnd);
		iLine = 0;
	}
	return iLine;
}

// ------------------------------------------------
// Window 1: Display increasing sequence of numbers
// ------------------------------------------------

void Thread1(PVOID pvoid)
{
	HDC     hdc;
	int     iNum = 0, iLine = 0;
	PPARAMS pparams;
	TCHAR   szBuffer[16];

	pparams = (PPARAMS)pvoid;

	while (!pparams->bKill)
	{
		if (iNum < 0)
			iNum = 0;

		iLine = CheckBottom(pparams->hwnd, pparams->cyClient,
			pparams->cyChar, iLine);

		hdc = GetDC(pparams->hwnd);

		TextOut(hdc, 0, iLine * pparams->cyChar, szBuffer,
			wsprintf(szBuffer, TEXT("%d"), iNum++));

		ReleaseDC(pparams->hwnd, hdc);
		iLine++;
	}
	_endthread();
}

LRESULT APIENTRY WndProc1(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static PARAMS params;

	switch (message)
	{
	case WM_CREATE:
		params.hwnd = hwnd;
		params.cyChar = HIWORD(GetDialogBaseUnits());
		_beginthread(Thread1, 0, &params);
		return 0;

	case WM_SIZE:
		params.cyClient = GET_Y_LPARAM(lParam);
		return 0;

	case WM_DESTROY:
		params.bKill = TRUE;
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}

// ------------------------------------------------------
// Window 2: Display increasing sequence of prime numbers
// ------------------------------------------------------

void Thread2(PVOID pvoid)
{
	HDC     hdc;
	int     iNum = 1, iLine = 0, i, iSqrt;
	PPARAMS pparams;
	TCHAR   szBuffer[16];

	pparams = (PPARAMS)pvoid;

	while (!pparams->bKill)
	{
		do
		{
			if (++iNum < 0)
				iNum = 0;

			iSqrt = (int)sqrt(iNum);

			for (i = 2; i <= iSqrt; i++)
				if (iNum % i == 0)
					break;
		} while (i <= iSqrt);

		iLine = CheckBottom(pparams->hwnd, pparams->cyClient,
			pparams->cyChar, iLine);

		hdc = GetDC(pparams->hwnd);

		TextOut(hdc, 0, iLine * pparams->cyChar, szBuffer,
			wsprintf(szBuffer, TEXT("%d"), iNum));

		ReleaseDC(pparams->hwnd, hdc);
		iLine++;
	}
	_endthread();
}

LRESULT APIENTRY WndProc2(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static PARAMS params;

	switch (message)
	{
	case WM_CREATE:
		params.hwnd = hwnd;
		params.cyChar = HIWORD(GetDialogBaseUnits());
		_beginthread(Thread2, 0, &params);
		return 0;

	case WM_SIZE:
		params.cyClient = GET_Y_LPARAM(lParam);
		return 0;

	case WM_DESTROY:
		params.bKill = TRUE;
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}

// Window 3: Display increasing sequence of Fibonacci numbers
// ----------------------------------------------------------

void Thread3(PVOID pvoid)
{
	HDC     hdc;
	int     iNum = 0, iNext = 1, iLine = 0, iTemp;
	PPARAMS pparams;
	TCHAR   szBuffer[16];

	pparams = (PPARAMS)pvoid;

	while (!pparams->bKill)
	{
		if (iNum < 0)
		{
			iNum = 0;
			iNext = 1;
		}
		iLine = CheckBottom(pparams->hwnd, pparams->cyClient,
			pparams->cyChar, iLine);

		hdc = GetDC(pparams->hwnd);

		TextOut(hdc, 0, iLine * pparams->cyChar, szBuffer,
			wsprintf(szBuffer, TEXT("%d"), iNum));

		ReleaseDC(pparams->hwnd, hdc);
		iTemp = iNum;
		iNum = iNext;
		iNext += iTemp;
		iLine++;
	}
	_endthread();
}

LRESULT APIENTRY WndProc3(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static PARAMS params;

	switch (message)
	{
	case WM_CREATE:
		params.hwnd = hwnd;
		params.cyChar = HIWORD(GetDialogBaseUnits());
		_beginthread(Thread3, 0, &params);
		return 0;

	case WM_SIZE:
		params.cyClient = GET_Y_LPARAM(lParam);
		return 0;

	case WM_DESTROY:
		params.bKill = TRUE;
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}

// -----------------------------------------
// Window 4: Display circles of random radii
// -----------------------------------------

void Thread4(PVOID pvoid)
{
	HDC     hdc;
	int     iDiameter;
	PPARAMS pparams;

	pparams = (PPARAMS)pvoid;

	while (!pparams->bKill)
	{
		InvalidateRect(pparams->hwnd, NULL, TRUE);
		UpdateWindow(pparams->hwnd);

		iDiameter = rand() % (max(1,
			min(pparams->cxClient, pparams->cyClient)));

		hdc = GetDC(pparams->hwnd);

		Ellipse(hdc, (pparams->cxClient - iDiameter) / 2,
			(pparams->cyClient - iDiameter) / 2,
			(pparams->cxClient + iDiameter) / 2,
			(pparams->cyClient + iDiameter) / 2);

		ReleaseDC(pparams->hwnd, hdc);
	}
	_endthread();
}

LRESULT APIENTRY WndProc4(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static PARAMS params;

	switch (message)
	{
	case WM_CREATE:
		params.hwnd = hwnd;
		params.cyChar = HIWORD(GetDialogBaseUnits());
		_beginthread(Thread4, 0, &params);
		return 0;

	case WM_SIZE:
		params.cxClient = GET_X_LPARAM(lParam);
		params.cyClient = GET_Y_LPARAM(lParam);
		return 0;

	case WM_DESTROY:
		params.bKill = TRUE;
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}

// -----------------------------------
// Main window to create child windows
// -----------------------------------

LRESULT APIENTRY WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HWND    hwndChild[4];
	static TCHAR* szChildClass[] = { TEXT("Child1"), TEXT("Child2"),
									  TEXT("Child3"), TEXT("Child4") };
	static WNDPROC ChildProc[] = { WndProc1, WndProc2, WndProc3, WndProc4 };
	HINSTANCE      hInstance;
	int            i, cxClient, cyClient;
	WNDCLASS       wndclass;

	switch (message)
	{
	case WM_CREATE:
		hInstance = (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE);

		wndclass.style = CS_HREDRAW | CS_VREDRAW;
		wndclass.cbClsExtra = 0;
		wndclass.cbWndExtra = 0;
		wndclass.hInstance = hInstance;
		wndclass.hIcon = NULL;
		wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
		wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
		wndclass.lpszMenuName = NULL;

		for (i = 0; i < 4; i++)
		{
			wndclass.lpfnWndProc = ChildProc[i];
			wndclass.lpszClassName = szChildClass[i];

			RegisterClass(&wndclass);

			hwndChild[i] = CreateWindow(szChildClass[i], NULL,
				WS_CHILDWINDOW | WS_BORDER | WS_VISIBLE,
				0, 0, 0, 0,
				hwnd, (HMENU)i, hInstance, NULL);
		}

		return 0;

	case WM_SIZE:
		cxClient = GET_X_LPARAM(lParam);
		cyClient = GET_Y_LPARAM(lParam);

		for (i = 0; i < 4; i++)
			MoveWindow(hwndChild[i], (i % 2) * cxClient / 2,
			(i > 1) * cyClient / 2,
				cxClient / 2, cyClient / 2, TRUE);
		return 0;

	case WM_CHAR:
		if (wParam == '\x1B')
			DestroyWindow(hwnd);

		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}
