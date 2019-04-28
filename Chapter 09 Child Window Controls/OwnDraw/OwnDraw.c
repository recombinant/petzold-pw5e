/*---------------------------------------------
   OWNDRAW.C -- Owner-Draw Button Demo Program
				(c) Charles Petzold, 1998
  ---------------------------------------------*/

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <windowsx.h>
#include <tchar.h>

#define ID_SMALLER 1
#define ID_LARGER  2

#define BTN_WIDTH  (8 * cxChar)
#define BTN_HEIGHT (4 * cyChar)

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

	static TCHAR szAppName[] = TEXT("OwnDraw");
	MSG          msg;
	HWND         hwnd;
	WNDCLASS     wndclass;

	hInst = hInstance;

	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = GetStockBrush(WHITE_BRUSH);
	wndclass.lpszMenuName = szAppName;
	wndclass.lpszClassName = szAppName;

	if (!RegisterClass(&wndclass))
	{
		MessageBox(NULL, TEXT("This program requires Windows NT!"),
			szAppName, MB_ICONERROR);
		return 0;
	}

	hwnd = CreateWindow(szAppName, TEXT("Owner-Draw Button Demo"),
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


void Triangle(HDC hdc, POINT pt[])
{
	SelectBrush(hdc, GetStockBrush(BLACK_BRUSH));
	Polygon(hdc, pt, 3);
	SelectBrush(hdc, GetStockBrush(WHITE_BRUSH));
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HWND      hwndSmaller, hwndLarger;
	static int       cxClient, cyClient, cxChar, cyChar;
	int              cx, cy;
	LPDRAWITEMSTRUCT pdis;
	POINT            pt[3];
	RECT             rc;

	switch (message)
	{
	case WM_CREATE:
		cxChar = LOWORD(GetDialogBaseUnits());
		cyChar = HIWORD(GetDialogBaseUnits());

		// Create the owner-draw pushbuttons

		hwndSmaller = CreateWindow(TEXT("button"), TEXT(""),
			WS_CHILD | WS_VISIBLE | BS_OWNERDRAW,
			0, 0, BTN_WIDTH, BTN_HEIGHT,
			hwnd, (HMENU)ID_SMALLER, hInst, NULL);

		hwndLarger = CreateWindow(TEXT("button"), TEXT(""),
			WS_CHILD | WS_VISIBLE | BS_OWNERDRAW,
			0, 0, BTN_WIDTH, BTN_HEIGHT,
			hwnd, (HMENU)ID_LARGER, hInst, NULL);
		return 0;

	case WM_SIZE:
		cxClient = GET_X_LPARAM(lParam);
		cyClient = GET_Y_LPARAM(lParam);

		// Move the buttons to the new center

		MoveWindow(hwndSmaller, cxClient / 2 - 3 * BTN_WIDTH / 2,
			cyClient / 2 - BTN_HEIGHT / 2,
			BTN_WIDTH, BTN_HEIGHT, TRUE);

		MoveWindow(hwndLarger, cxClient / 2 + BTN_WIDTH / 2,
			cyClient / 2 - BTN_HEIGHT / 2,
			BTN_WIDTH, BTN_HEIGHT, TRUE);
		return 0;

	case WM_COMMAND:
		GetWindowRect(hwnd, &rc);

		// Make the window 10% smaller or larger

		switch (wParam)
		{
		case ID_SMALLER:
			rc.left += cxClient / 20;
			rc.right -= cxClient / 20;
			rc.top += cyClient / 20;
			rc.bottom -= cyClient / 20;
			break;

		case ID_LARGER:
			rc.left -= cxClient / 20;
			rc.right += cxClient / 20;
			rc.top -= cyClient / 20;
			rc.bottom += cyClient / 20;
			break;
		}

		MoveWindow(hwnd, rc.left, rc.top, rc.right - rc.left,
			rc.bottom - rc.top, TRUE);
		return 0;

	case WM_DRAWITEM:
		pdis = (LPDRAWITEMSTRUCT)lParam;

		// Fill area with white and frame it black

		FillRect(pdis->hDC, &pdis->rcItem, GetStockBrush(WHITE_BRUSH));

		FrameRect(pdis->hDC, &pdis->rcItem, GetStockBrush(BLACK_BRUSH));

		// Draw inward and outward black triangles

		cx = pdis->rcItem.right - pdis->rcItem.left;
		cy = pdis->rcItem.bottom - pdis->rcItem.top;

		switch (pdis->CtlID)
		{
		case ID_SMALLER:
			pt[0].x = 3 * cx / 8;  pt[0].y = 1 * cy / 8;
			pt[1].x = 5 * cx / 8;  pt[1].y = 1 * cy / 8;
			pt[2].x = 4 * cx / 8;  pt[2].y = 3 * cy / 8;

			Triangle(pdis->hDC, pt);

			pt[0].x = 7 * cx / 8;  pt[0].y = 3 * cy / 8;
			pt[1].x = 7 * cx / 8;  pt[1].y = 5 * cy / 8;
			pt[2].x = 5 * cx / 8;  pt[2].y = 4 * cy / 8;

			Triangle(pdis->hDC, pt);

			pt[0].x = 5 * cx / 8;  pt[0].y = 7 * cy / 8;
			pt[1].x = 3 * cx / 8;  pt[1].y = 7 * cy / 8;
			pt[2].x = 4 * cx / 8;  pt[2].y = 5 * cy / 8;

			Triangle(pdis->hDC, pt);

			pt[0].x = 1 * cx / 8;  pt[0].y = 5 * cy / 8;
			pt[1].x = 1 * cx / 8;  pt[1].y = 3 * cy / 8;
			pt[2].x = 3 * cx / 8;  pt[2].y = 4 * cy / 8;

			Triangle(pdis->hDC, pt);
			break;

		case ID_LARGER:
			pt[0].x = 5 * cx / 8;  pt[0].y = 3 * cy / 8;
			pt[1].x = 3 * cx / 8;  pt[1].y = 3 * cy / 8;
			pt[2].x = 4 * cx / 8;  pt[2].y = 1 * cy / 8;

			Triangle(pdis->hDC, pt);

			pt[0].x = 5 * cx / 8;  pt[0].y = 5 * cy / 8;
			pt[1].x = 5 * cx / 8;  pt[1].y = 3 * cy / 8;
			pt[2].x = 7 * cx / 8;  pt[2].y = 4 * cy / 8;

			Triangle(pdis->hDC, pt);

			pt[0].x = 3 * cx / 8;  pt[0].y = 5 * cy / 8;
			pt[1].x = 5 * cx / 8;  pt[1].y = 5 * cy / 8;
			pt[2].x = 4 * cx / 8;  pt[2].y = 7 * cy / 8;

			Triangle(pdis->hDC, pt);

			pt[0].x = 3 * cx / 8;  pt[0].y = 3 * cy / 8;
			pt[1].x = 3 * cx / 8;  pt[1].y = 5 * cy / 8;
			pt[2].x = 1 * cx / 8;  pt[2].y = 4 * cy / 8;

			Triangle(pdis->hDC, pt);
			break;
		}

		// Invert the rectangle if the button is selected

		if (pdis->itemState & ODS_SELECTED)
			InvertRect(pdis->hDC, &pdis->rcItem);

		// Draw a focus rectangle if the button has the focus

		if (pdis->itemState & ODS_FOCUS)
		{
			pdis->rcItem.left += cx / 16;
			pdis->rcItem.top += cy / 16;
			pdis->rcItem.right -= cx / 16;
			pdis->rcItem.bottom -= cy / 16;

			DrawFocusRect(pdis->hDC, &pdis->rcItem);
		}
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}
