/*-------------------------------------
   GETPRNDC.C -- GetPrinterDC function
  -------------------------------------*/

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <winspool.h>
#include <malloc.h>

HDC GetPrinterDC(void)
{
	/* The original GetPrinterDC() function checked  for Windows 98
	 * or Windows NT.
	 */
	DWORD dwNeeded, dwReturned;

	EnumPrinters(PRINTER_ENUM_LOCAL, NULL, 4, NULL, 0, &dwNeeded, &dwReturned);

	PRINTER_INFO_4* pinfo4 = malloc(dwNeeded);

	EnumPrinters(PRINTER_ENUM_LOCAL, NULL, 4, (PBYTE)pinfo4, dwNeeded, &dwNeeded, &dwReturned);

	HDC hdc = CreateDC(NULL, pinfo4->pPrinterName, NULL, NULL);

	free(pinfo4);

	return hdc;
}
