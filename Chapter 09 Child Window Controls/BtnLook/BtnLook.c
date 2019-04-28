/*----------------------------------------
   BTNLOOK.C -- Button Look Program
				(c) Charles Petzold, 1998
  ----------------------------------------*/

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <windowsx.h>
#include <tchar.h>
#include <stdlib.h>

struct
{
	int     iStyle;
	TCHAR* szText;
}
button[] =
{
	{BS_PUSHBUTTON,      TEXT("PUSHBUTTON")},
	{BS_DEFPUSHBUTTON,   TEXT("DEFPUSHBUTTON")},
	{BS_CHECKBOX,        TEXT("CHECKBOX")},
	{BS_AUTOCHECKBOX,    TEXT("AUTOCHECKBOX")},
	{BS_RADIOBUTTON,     TEXT("RADIOBUTTON")},
	{BS_3STATE,          TEXT("3STATE")},
	{BS_AUTO3STATE,      TEXT("AUTO3STATE")},
	{BS_GROUPBOX,        TEXT("GROUPBOX")},
	{BS_AUTORADIOBUTTON, TEXT("AUTORADIO")},
	{BS_OWNERDRAW,       TEXT("OWNERDRAW"})
};

#define NUM _countof(sizeof button)

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


int WINAPI _tWinMain(
	_In_     HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_     PTSTR     pCmdLine,
	_In_     int       nShowCmd)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(pCmdLine);

	static TCHAR szAppName[] = TEXT("BtnLook");
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
	wndclass.hbrBackground = GetStockBrush(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;

	if (!RegisterClass(&wndclass))
	{
		MessageBox(NULL, TEXT("This program requires Windows NT!"),
			szAppName, MB_ICONERROR);
		return 0;
	}

	hwnd = CreateWindow(szAppName, TEXT("Button Look"),
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
	static HWND  hwndButton[NUM];
	static RECT  rect;
	static TCHAR szTop[] = TEXT("message            wParam       lParam");
	static TCHAR szUnd[] = TEXT("_______            ______       ______");
	static TCHAR szFormat[] = TEXT("%-16s%04X-%04X    %04X-%04X");
	static TCHAR szBuffer[50];
	static int   cxChar, cyChar;
	HDC          hdc;
	PAINTSTRUCT  ps;

	switch (message)
	{
	case WM_CREATE:
		cxChar = LOWORD(GetDialogBaseUnits());
		cyChar = HIWORD(GetDialogBaseUnits());

		for (unsigned i = 0; i < NUM; i++)
			hwndButton[i] = CreateWindowEx(0, TEXT("button"),
				button[i].szText,
				WS_CHILD | WS_VISIBLE | button[i].iStyle,
				cxChar, cyChar * (1 + 2 * i),
				20 * cxChar, 7 * cyChar / 4,
				hwnd, (HMENU)i,
				((LPCREATESTRUCT)lParam)->hInstance, NULL);
		return 0;

	case WM_SIZE:
		rect.left = 24 * cxChar;
		rect.top = 2 * cyChar;
		rect.right = GET_X_LPARAM(lParam);
		rect.bottom = GET_Y_LPARAM(lParam);
		return 0;

	case WM_PAINT:
		InvalidateRect(hwnd, &rect, TRUE);

		hdc = BeginPaint(hwnd, &ps);
		SelectFont(hdc, GetStockFont(SYSTEM_FIXED_FONT));
		SetBkMode(hdc, TRANSPARENT);

		TextOut(hdc, 24 * cxChar, cyChar, szTop, lstrlen(szTop));
		TextOut(hdc, 24 * cxChar, cyChar, szUnd, lstrlen(szUnd));

		EndPaint(hwnd, &ps);
		return 0;

	case WM_DRAWITEM:
	case WM_COMMAND:
		ScrollWindow(hwnd, 0, -cyChar, &rect, &rect);

		hdc = GetDC(hwnd);
		SelectFont(hdc, GetStockFont(SYSTEM_FIXED_FONT));

		TextOut(hdc, 24 * cxChar, cyChar * (rect.bottom / cyChar - 1),
			szBuffer,
			wsprintf(szBuffer, szFormat,
				message == WM_DRAWITEM ? TEXT("WM_DRAWITEM") :
				TEXT("WM_COMMAND"),
				HIWORD(wParam), LOWORD(wParam),
				HIWORD(lParam), LOWORD(lParam)));

		ReleaseDC(hwnd, hdc);
		ValidateRect(hwnd, &rect);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}
