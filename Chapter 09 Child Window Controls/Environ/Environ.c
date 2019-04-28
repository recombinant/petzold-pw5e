/*----------------------------------------
   ENVIRON.C -- Environment List Box
				(c) Charles Petzold, 1998
  ----------------------------------------*/

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <windowsx.h>
#include <tchar.h>
#include <malloc.h>


#define ID_LIST     1
#define ID_TEXT     2

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI _tWinMain(
	_In_     HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_     PTSTR     pCmdLine,
	_In_     int       nShowCmd)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(pCmdLine);

	static TCHAR szAppName[] = TEXT("Environ");
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
	wndclass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;

	if (!RegisterClass(&wndclass))
	{
		MessageBox(NULL, TEXT("This program requires Windows NT!"),
			szAppName, MB_ICONERROR);
		return 0;
	}

	hwnd = CreateWindow(szAppName, TEXT("Environment List Box"),
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


void FillListBox(HWND hwndList)
{
	int    iLength;
	TCHAR* pEBlock, * pVarBlock, * pVarBeg, * pVarEnd, * pVarName;

	pEBlock = GetEnvironmentStrings();  // Get pointer to environment block
	pVarBlock = pEBlock;

	while (*pVarBlock)
	{
		if (*pVarBlock != '=')   // Skip variable names beginning with '='
		{
			pVarBeg = pVarBlock;              // Beginning of variable name
			while (*pVarBlock++ != '=');      // Scan until '='
			pVarEnd = pVarBlock - 1;          // Points to '=' sign
			iLength = pVarEnd - pVarBeg;      // Length of variable name

				 // Allocate memory for the variable name and terminating
				 // zero. Copy the variable name and append a zero.

			pVarName = calloc(iLength + 1, sizeof(TCHAR));
			CopyMemory(pVarName, pVarBeg, iLength * sizeof(TCHAR));
			pVarName[iLength] = '\0';

			// Put the variable name in the list box and free memory.

			SendMessage(hwndList, LB_ADDSTRING, 0, (LPARAM)pVarName);
			free(pVarName);
		}
		while (*pVarBlock++ != '\0');     // Scan until terminating zero
	}
	FreeEnvironmentStrings(pEBlock);
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HWND  hwndList, hwndText;
	int          iIndex, iLength, cxChar, cyChar;
	TCHAR* pVarName, * pVarValue;

	switch (message)
	{
	case WM_CREATE:
		cxChar = LOWORD(GetDialogBaseUnits());
		cyChar = HIWORD(GetDialogBaseUnits());

		// Create listbox and static text windows.

		hwndList = CreateWindow(TEXT("listbox"), NULL,
			WS_CHILD | WS_VISIBLE | LBS_STANDARD,
			cxChar, cyChar * 3,
			cxChar * 16 + GetSystemMetrics(SM_CXVSCROLL),
			cyChar * 5,
			hwnd, (HMENU)ID_LIST,
			GetWindowInstance(hwnd),
			NULL);

		hwndText = CreateWindow(TEXT("static"), NULL,
			WS_CHILD | WS_VISIBLE | SS_LEFT,
			cxChar, cyChar,
			GetSystemMetrics(SM_CXSCREEN), cyChar,
			hwnd, (HMENU)ID_TEXT,
			GetWindowInstance(hwnd),
			NULL);

		FillListBox(hwndList);
		return 0;

	case WM_SETFOCUS:
		SetFocus(hwndList);
		return 0;

	case WM_COMMAND:
		if (LOWORD(wParam) == ID_LIST && HIWORD(wParam) == LBN_SELCHANGE)
		{
			// Get current selection.

			iIndex = ListBox_GetCurSel(hwndList);
			iLength = ListBox_GetTextLen(hwndList, iIndex) + 1;
			pVarName = calloc(iLength, sizeof(TCHAR));
			ListBox_GetText(hwndList, iIndex, pVarName);

			// Get environment string.

			iLength = GetEnvironmentVariable(pVarName, NULL, 0);
			pVarValue = calloc(iLength, sizeof(TCHAR));
			GetEnvironmentVariable(pVarName, pVarValue, iLength);

			// Show it in window.

			SetWindowText(hwndText, pVarValue);
			free(pVarName);
			free(pVarValue);
		}
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}
