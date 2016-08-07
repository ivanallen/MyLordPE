#pragma once
#include <windows.h>
#include <AtlConv.h>
#include <CommCtrl.h>
#include <Richedit.h>
#include <TlHelp32.h>
#include <stdio.h>
#include <stdlib.h>
#include "resource.h"
#include "pe.h"
#pragma comment(lib, "comctl32.lib")

#ifdef UNICODE
#define stprintf swprintf_s
#else
#define stprintf sprintf_s
#endif
extern HINSTANCE hAppInstance;
extern HPE pe;
extern char szInfo[1024*512];
VOID CenterWindow(IN HWND hWnd);
VOID OpenFileWindow(IN HWND hWnd, IN TCHAR* filter, OUT TCHAR* szFileName, IN int length);

