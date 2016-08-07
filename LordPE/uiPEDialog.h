#pragma once
#include "Common.h"


BOOL CALLBACK DialogPEProc( HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam );
VOID OnInitDialogPE(HWND hWnd);
VOID OnSectionButtonClicked(HWND hWnd);
VOID OnDirectoryButtonClicked(HWND hWnd);