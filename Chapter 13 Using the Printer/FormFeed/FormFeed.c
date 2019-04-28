/*---------------------------------------------
   FORMFEED.C -- Advances printer to next page
				 (c) Charles Petzold, 1998
  ---------------------------------------------*/

#define WIN32_LEAN_AND_MEAN
#include <tchar.h>
#include <windows.h>

HDC GetPrinterDC(void);

int WINAPI _tWinMain(
	_In_     HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_     PTSTR     pCmdLine,
	_In_     int       nShowCmd)
{
	UNREFERENCED_PARAMETER(hInstance);
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(pCmdLine);
	UNREFERENCED_PARAMETER(nShowCmd);

	static DOCINFO di = { .cbSize = sizeof(DOCINFO),.lpszDocName = TEXT("FormFeed") };
	HDC            hdcPrint = GetPrinterDC();

	if (hdcPrint != NULL)
	{
		if (StartDoc(hdcPrint, &di) > 0)
			if (StartPage(hdcPrint) > 0 && EndPage(hdcPrint) > 0)
				EndDoc(hdcPrint);

		DeleteDC(hdcPrint);
	}
	return 0;
}
