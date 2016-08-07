#pragma once
#include "Common.h"

BOOL CALLBACK DialogSectionProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
VOID OnInitDialogSection( HWND hWnd );
VOID InitListSection(HWND hWnd);
VOID InsertListSection(HWND hWnd, int index, TCHAR *szName, DWORD FOA, DWORD sizeOfRawData, DWORD RVA, DWORD virtualSize, DWORD characteristics);