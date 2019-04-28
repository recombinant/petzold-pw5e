/*----------------------------------------
   COLORS1.C -- Colors Using Scroll Bars
				(c) Charles Petzold, 1998
  ----------------------------------------*/

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <windowsx.h>
#include <tchar.h>
#include <commctrl.h>


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ScrollProc(HWND, UINT, WPARAM, LPARAM, UINT_PTR, DWORD_PTR);

#define N (3)  // Number of colors.

int idFocus;


int WINAPI _tWinMain(
	_In_     HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_     PTSTR     pCmdLine,
	_In_     int       nShowCmd)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(pCmdLine);

	static TCHAR szAppName[] = TEXT("Colors1");
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
	wndclass.hbrBackground = CreateSolidBrush(0);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;

	if (!RegisterClass(&wndclass))
	{
		MessageBox(NULL, TEXT("This program requires Windows NT!"),
			szAppName, MB_ICONERROR);
		return 0;
	}

	hwnd = CreateWindow(szAppName, TEXT("Color Scroll"),
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
	static COLORREF crPrim[N] = { RGB(255, 0, 0), RGB(0, 255, 0),
								  RGB(0, 0, 255) };
	static HBRUSH  hBrush[N], hBrushStatic;
	static HWND    hwndScroll[N], hwndLabel[N], hwndValue[N], hwndRect;
	static int     color[N], cyChar;
	static RECT    rcColor;
	static TCHAR* szColorLabel[] = { TEXT("Red"), TEXT("Green"),
									  TEXT("Blue") };
	HINSTANCE      hInstance;
	int            i, cxClient, cyClient;
	TCHAR          szBuffer[10];

	switch (message)
	{
	case WM_CREATE:
		hInstance = GetWindowInstance(hwnd);

		// Create the white-rectangle window against which the
		// scroll bars will be positioned. The child window ID is 9.

		hwndRect = CreateWindow(TEXT("static"), NULL,
			WS_CHILD | WS_VISIBLE | SS_WHITERECT,
			0, 0, 0, 0,
			hwnd, (HMENU)9, hInstance, NULL);

		for (i = 0; i < N; i++)
		{
			// The three scroll bars have IDs 0, 1, and 2, with
			// scroll bar ranges from 0 through 255.

			hwndScroll[i] = CreateWindow(TEXT("scrollbar"), NULL,
				WS_CHILD | WS_VISIBLE |
				WS_TABSTOP | SBS_VERT,
				0, 0, 0, 0,
				hwnd, (HMENU)i, hInstance, NULL);

			SetScrollRange(hwndScroll[i], SB_CTL, 0, 255, FALSE);
			SetScrollPos(hwndScroll[i], SB_CTL, 0, FALSE);

			// The three color-name labels have IDs 3, 4, and 5,
			// and text strings "Red", "Green", and "Blue".

			hwndLabel[i] = CreateWindow(TEXT("static"), szColorLabel[i],
				WS_CHILD | WS_VISIBLE | SS_CENTER,
				0, 0, 0, 0,
				hwnd, (HMENU)(i + N),
				hInstance, NULL);

			// The three color-value text fields have IDs 6, 7,
			// and 8, and initial text strings of "0".

			hwndValue[i] = CreateWindow(TEXT("static"), TEXT("0"),
				WS_CHILD | WS_VISIBLE | SS_CENTER,
				0, 0, 0, 0,
				hwnd, (HMENU)(i + 2 * N),
				hInstance, NULL);

			SetWindowSubclass(hwnd, ScrollProc, (UINT_PTR)i, 0);

			hBrush[i] = CreateSolidBrush(crPrim[i]);
		}

		hBrushStatic = CreateSolidBrush(
			GetSysColor(COLOR_BTNHIGHLIGHT));

		cyChar = HIWORD(GetDialogBaseUnits());
		return 0;

	case WM_SIZE:
		cxClient = GET_X_LPARAM(lParam);
		cyClient = GET_Y_LPARAM(lParam);

		SetRect(&rcColor, cxClient / 2, 0, cxClient, cyClient);

		MoveWindow(hwndRect, 0, 0, cxClient / 2, cyClient, TRUE);

		for (i = 0; i < N; i++)
		{
			MoveWindow(hwndScroll[i],
				(2 * i + 1) * cxClient / 14, 2 * cyChar,
				cxClient / 14, cyClient - 4 * cyChar, TRUE);

			MoveWindow(hwndLabel[i],
				(4 * i + 1) * cxClient / 28, cyChar / 2,
				cxClient / 7, cyChar, TRUE);

			MoveWindow(hwndValue[i],
				(4 * i + 1) * cxClient / 28,
				cyClient - 3 * cyChar / 2,
				cxClient / 7, cyChar, TRUE);
		}
		SetFocus(hwnd);
		return 0;

	case WM_SETFOCUS:
		SetFocus(hwndScroll[idFocus]);
		return 0;

	case WM_VSCROLL:
		i = GetWindowLongPtr((HWND)lParam, GWLP_ID);

		switch (LOWORD(wParam))
		{
		case SB_PAGEDOWN:
			color[i] += 15;
			// fall through
		case SB_LINEDOWN:
			color[i] = min(255, color[i] + 1);
			break;

		case SB_PAGEUP:
			color[i] -= 15;
			// fall through
		case SB_LINEUP:
			color[i] = max(0, color[i] - 1);
			break;

		case SB_TOP:
			color[i] = 0;
			break;

		case SB_BOTTOM:
			color[i] = 255;
			break;

		case SB_THUMBPOSITION:
		case SB_THUMBTRACK:
			color[i] = HIWORD(wParam);
			break;

		default:
			break;
		}
		SetScrollPos(hwndScroll[i], SB_CTL, color[i], TRUE);
		wsprintf(szBuffer, TEXT("%i"), color[i]);
		SetWindowText(hwndValue[i], szBuffer);

		DeleteBrush((HBRUSH)
			SetClassLongPtr(hwnd, GCLP_HBRBACKGROUND, (LONG_PTR)
				CreateSolidBrush(RGB(color[0], color[1], color[2]))));

		InvalidateRect(hwnd, &rcColor, TRUE);
		return 0;

	case WM_CTLCOLORSCROLLBAR:
		i = GetWindowLongPtr((HWND)lParam, GWLP_ID);
		return (LRESULT)hBrush[i];

	case WM_CTLCOLORSTATIC:
		i = GetWindowLongPtr((HWND)lParam, GWLP_ID);

		if (i >= N && i <= 8)    // static text controls
		{
			SetTextColor((HDC)wParam, crPrim[i % N]);
			SetBkColor((HDC)wParam, GetSysColor(COLOR_BTNHIGHLIGHT));
			return (LRESULT)hBrushStatic;
		}
		break;

	case WM_SYSCOLORCHANGE:
		DeleteBrush(hBrushStatic);
		hBrushStatic = CreateSolidBrush(GetSysColor(COLOR_BTNHIGHLIGHT));
		return 0;

	case WM_DESTROY:
		DeleteBrush((HBRUSH)
			SetClassLongPtr(hwnd, GCLP_HBRBACKGROUND, (LONG_PTR)GetStockBrush(WHITE_BRUSH)));

		for (i = 0; i < N; i++)
		{
			DeleteBrush(hBrush[i]);
		}

		DeleteBrush(hBrushStatic);
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}


LRESULT CALLBACK ScrollProc(
	HWND hwnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam,
	UINT_PTR uIdSubclass,
	DWORD_PTR dwRefData)
{
	UNREFERENCED_PARAMETER(uIdSubclass);
	UNREFERENCED_PARAMETER(dwRefData);

	int id = GetWindowLongPtr(hwnd, GWLP_ID);

	switch (uMsg)
	{
	case WM_KEYDOWN:
		if (wParam == VK_TAB)
		{
			SetFocus(GetDlgItem(GetParent(hwnd),
				(id + (GetKeyState(VK_SHIFT) < 0 ? 2 : 1)) % N));
		}
		break;

	case WM_NCDESTROY:
		RemoveWindowSubclass(hwnd, ScrollProc, id);
		break;

	case WM_SETFOCUS:
		idFocus = id;
		break;
	}
	return DefSubclassProc(hwnd, uMsg, wParam, lParam);
}
