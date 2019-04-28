/*---------------------------------------------
   HEAD.C -- Displays beginning (head) of file
			 (c) Charles Petzold, 1998
  ---------------------------------------------*/

#define WIN32_LEAN_AND_MEAN
#undef NOUSER

#include <windows.h>
#include <windowsx.h>
#include <tchar.h>
#include <commctrl.h>


#define ID_LIST     1
#define ID_TEXT     2

#define MAXREAD     8192
#define DIRATTR     (DDL_READWRITE | DDL_READONLY | DDL_HIDDEN | DDL_SYSTEM | \
                     DDL_DIRECTORY | DDL_ARCHIVE  | DDL_DRIVES)
#define DTFLAGS     (DT_WORDBREAK | DT_EXPANDTABS | DT_NOCLIP | DT_NOPREFIX)

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ListProc(HWND, UINT, WPARAM, LPARAM, UINT_PTR, DWORD_PTR);


int WINAPI _tWinMain(
	_In_     HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_     PTSTR     pCmdLine,
	_In_     int       nShowCmd)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(pCmdLine);

	static TCHAR szAppName[] = TEXT("head");
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
	wndclass.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;

	if (!RegisterClass(&wndclass))
	{
		MessageBox(NULL, TEXT("This program requires Windows NT!"),
			szAppName, MB_ICONERROR);
		return 0;
	}

	hwnd = CreateWindow(szAppName, TEXT("head"),
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


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static BOOL     bValidFile;
	static TCHAR    buffer[MAXREAD];
	static HWND     hwndList, hwndText;
	static RECT     rect;
	static TCHAR    szFile[MAX_PATH + 1];
	HANDLE          hFile;
	HDC             hdc;
	int             cxChar, cyChar;
	DWORD           nBytesRead;
	PAINTSTRUCT     ps;
	TCHAR           szBuffer[MAX_PATH + 1];

	switch (message)
	{
	case WM_CREATE:
		cxChar = LOWORD(GetDialogBaseUnits());
		cyChar = HIWORD(GetDialogBaseUnits());

		rect.left = 20 * cxChar;
		rect.top = 3 * cyChar;

		hwndList = CreateWindowEx(0, TEXT("listbox"), NULL,
			WS_CHILDWINDOW | WS_VISIBLE | LBS_STANDARD,
			cxChar, cyChar * 3,
			cxChar * 13 + GetSystemMetrics(SM_CXVSCROLL),
			cyChar * 10,
			hWnd, (HMENU)ID_LIST,
			GetWindowInstance(hWnd),
			NULL);

		GetCurrentDirectory(MAX_PATH + 1, szBuffer);

		hwndText = CreateWindowEx(0, TEXT("static"), szBuffer,
			WS_CHILDWINDOW | WS_VISIBLE | SS_LEFT,
			cxChar, cyChar, cxChar * MAX_PATH, cyChar,
			hWnd, (HMENU)ID_TEXT,
			GetWindowInstance(hWnd),
			NULL);

		SetWindowSubclass(hwndList, ListProc, ID_LIST, (DWORD_PTR)0);

		ListBox_Dir(hwndList, DIRATTR, TEXT("*.*"));

		return 0;

	case WM_SIZE:
		rect.right = GET_X_LPARAM(lParam);
		rect.bottom = GET_Y_LPARAM(lParam);
		return 0;

	case WM_SETFOCUS:
		SetFocus(hwndList);
		return 0;

	case WM_COMMAND:
		if (GET_WM_COMMAND_ID(wParam, lParam) == ID_LIST && GET_WM_COMMAND_CMD(wParam, lParam) == LBN_DBLCLK)
		{
			int i = ListBox_GetCurSel(hwndList);
			if (LB_ERR == i)
			{
				break;
			}

			ListBox_GetText(hwndList, i, szBuffer);

			hFile = CreateFile(szBuffer, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
			if (INVALID_HANDLE_VALUE != hFile)
			{
				CloseHandle(hFile);
				bValidFile = TRUE;
				lstrcpy(szFile, szBuffer);
				GetCurrentDirectory(MAX_PATH + 1, szBuffer);

				if (szBuffer[lstrlen(szBuffer) - 1] != '\\')
					lstrcat(szBuffer, TEXT("\\"));
				SetWindowText(hwndText, lstrcat(szBuffer, szFile));
			}
			else {
				bValidFile = FALSE;
				szBuffer[lstrlen(szBuffer) - 1] = '\0';

				// If setting the directory doesn't work, maybe it's
				// a drive change, so try that.

				if (!SetCurrentDirectory(szBuffer + 1))
				{
					szBuffer[3] = ':';
					szBuffer[4] = '\0';
					SetCurrentDirectory(szBuffer + 2);
				}

				// Get the new directory name and fill the list box.

				GetCurrentDirectory(MAX_PATH + 1, szBuffer);
				SetWindowText(hwndText, szBuffer);
				ListBox_ResetContent(hwndList);
				ListBox_Dir(hwndList, DIRATTR, TEXT("*.*"));
			}
			InvalidateRect(hWnd, NULL, TRUE);
		}
		return 0;

	case WM_PAINT:
		if (!bValidFile)
		{
			break;
		}

		hFile = CreateFile(szFile, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
		if (INVALID_HANDLE_VALUE == hFile)
		{
			bValidFile = FALSE;
			break;
		}

		ReadFile(hFile, buffer, MAXREAD, &nBytesRead, NULL);
		CloseHandle(hFile);

		// i now equals the number of bytes in buffer.
		// Commence getting a device context for displaying text.

		hdc = BeginPaint(hWnd, &ps);
		SelectFont(hdc, GetStockFont(SYSTEM_FIXED_FONT));
		SetTextColor(hdc, GetSysColor(COLOR_BTNTEXT));
		SetBkColor(hdc, GetSysColor(COLOR_BTNFACE));

		// Assume the file is ASCII

		DrawTextA(hdc, buffer, nBytesRead, &rect, DTFLAGS);

		EndPaint(hWnd, &ps);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}


LRESULT CALLBACK ListProc(
	HWND hwnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam,
	UINT_PTR uIdSubclass,
	DWORD_PTR dwRefData)
{
	UNREFERENCED_PARAMETER(uIdSubclass);
	UNREFERENCED_PARAMETER(dwRefData);

	switch (uMsg)
	{
	case WM_KEYDOWN:
		if (wParam == VK_RETURN)
		{
			SendMessage(GetParent(hwnd), WM_COMMAND,
				MAKELONG(ID_LIST, LBN_DBLCLK), (LPARAM)hwnd);
		}
		break;

	case WM_NCDESTROY:
		RemoveWindowSubclass(hwnd, ListProc, ID_LIST);
		break;


	default:
		break;
	}
	return DefSubclassProc(hwnd, uMsg, wParam, lParam);
}
