#pragma once
#include "Common.h"
#define SHOWEXPORT 1
#define SHOWIMPORT 2
#define SHOWRESOURCE 3
#define SHOWRELOCATION 4
#define SHOWBOUNDIMPORT 5
#define SHOWIAT 6
#define	SHOWNOTHING -1
extern int showmethod;
BOOL CALLBACK DialogInfoProc( HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam );
VOID OnInitDialogInfo(HWND hWnd);
VOID AppendTextToRichEdit(HWND hWnd, char* szText);
VOID ShowExport(HWND hWnd);
VOID ShowImport(HWND hWnd);
VOID ShowResource(HWND hWnd);
VOID ShowRelocation(HWND hWnd);
VOID ShowBoundImport(HWND hWnd);
VOID ShowIAT(HWND hWnd);

