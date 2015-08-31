/*-----------------------------------------------------
   ScrnSize.c -- Displays screen size in a message box
                 (c) Charles Petzold, 1998
  -----------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <tchar.h>

_Check_return_opt_
int __cdecl MessageBoxPrintf(
    _In_opt_ PCTSTR szCaption,
    _In_z_ _Printf_format_string_ PCTSTR szFormat,
    ...)
{
    TCHAR   szBuffer[1024];
    va_list pArgList;

        // The va_start macro (defined in STDARG.H) is usually equivalent to:
        // pArgList = (TCHAR *) &szFormat + sizeof (szFormat) ;

    va_start(pArgList, szFormat);

        // The last argument to wvsprintf_s points to the arguments

    _vsntprintf_s(szBuffer, _countof(szBuffer) - 1, _TRUNCATE, szFormat, pArgList);

        // The va_end macro just zeroes out pArgList for no good reason

    va_end(pArgList);

       // MessageBox() always returns IDOK with MB_OK

    return MessageBox(NULL, szBuffer, szCaption, MB_OK);
}

int WINAPI _tWinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ PTSTR lpCmdLine,
    _In_ int nShowCmd)
{
    int cxScreen = GetSystemMetrics(SM_CXSCREEN);
    int cyScreen = GetSystemMetrics(SM_CYSCREEN);

    MessageBoxPrintf(
        TEXT("ScrnSize"),
        TEXT("The screen is %i pixels wide by %i pixels high."),
        cxScreen, cyScreen);
    return 0;
}
