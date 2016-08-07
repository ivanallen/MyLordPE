//#include "stdafx.h"
#include "Common.h"
#include "uiMainDialog.h"

HINSTANCE hAppInstance;

int __stdcall WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd )
{
	hAppInstance = hInstance;
	INITCOMMONCONTROLSEX icex;
	icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
	icex.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&icex);
	HINSTANCE hModule = LoadLibrary(TEXT("riched20.dll"));
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG_MAIN), NULL, DialogMainProc);
	FreeLibrary(hModule);
	return 0;
}


