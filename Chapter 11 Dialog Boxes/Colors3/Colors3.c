/*----------------------------------------------
   COLORS3.C -- Version using Common Dialog Box
				(c) Charles Petzold, 1998
  ----------------------------------------------*/

#define WIN32_LEAN_AND_MEAN
#include <tchar.h>
#include <windows.h>
#include <commdlg.h>

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

	static CHOOSECOLOR cc;
	static COLORREF    crCustColors[16];

	cc.lStructSize = sizeof(CHOOSECOLOR);
	cc.hwndOwner = NULL;
	cc.hInstance = NULL;
	cc.rgbResult = RGB(0x80, 0x80, 0x80);
	cc.lpCustColors = crCustColors;
	cc.Flags = CC_RGBINIT | CC_FULLOPEN;
	cc.lCustData = 0;
	cc.lpfnHook = NULL;
	cc.lpTemplateName = NULL;

	return ChooseColor(&cc);
}
