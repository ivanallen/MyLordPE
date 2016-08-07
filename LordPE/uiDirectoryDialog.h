#pragma once
#include "Common.h"

BOOL CALLBACK DialogDirectoryProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);

VOID OnInitDialogDirectory(HWND hWnd);
VOID OnExportButtonClicked(HWND hWnd);
VOID OnImportButtonClicked(HWND hWnd);
VOID OnResourceButtonClicked(HWND hWnd);
VOID OnRelocationButtonClicked(HWND hWnd);
VOID OnBoundImportButtonClicked(HWND hWnd);
VOID OnIATButtonClicked(HWND hWnd);

