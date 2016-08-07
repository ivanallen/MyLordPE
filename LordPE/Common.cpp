#include "Common.h"

VOID CenterWindow( HWND hWnd)
{
	int scrWidth = GetSystemMetrics(SM_CXSCREEN);
	int scrHeight = GetSystemMetrics(SM_CYSCREEN);
	RECT rect = {0};
	GetWindowRect(hWnd, &rect);
	SetWindowPos(hWnd, HWND_TOPMOST, (scrWidth - rect.right) / 2, (scrHeight - rect.bottom) / 2, rect.right - rect.left, rect.bottom - rect.top, SWP_SHOWWINDOW);
}


VOID OpenFileWindow(HWND hWnd, IN TCHAR* filter, TCHAR* szFileName, int length)
{
	//TCHAR szPeFileExt[64] = TEXT("*.exe;*.dll;*.scr;*.drv;*.sys");

	OPENFILENAME stOpenFile = { 0 };

	stOpenFile.lStructSize = sizeof(OPENFILENAME);
	stOpenFile.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;
	stOpenFile.hwndOwner = hWnd;
	stOpenFile.lpstrFilter = filter;
	stOpenFile.lpstrFile = szFileName;
	stOpenFile.nMaxFile = length;
	GetOpenFileName(&stOpenFile);
}