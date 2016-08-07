#pragma once
#include "Common.h"


BOOL CALLBACK DialogMainProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);

VOID InitListProcess(HWND hWnd);
VOID InitListModule(HWND hWnd);
VOID OnInitDialogMain(HWND hWnd);
VOID OnOpenPeButtonClicked( HWND hWnd );
VOID OnListProcessClicked( HWND hWnd, WPARAM wParam, LPARAM lParam );
VOID InsertListProcess(HWND hWnd, int index, TCHAR* szProcessName, DWORD pid, DWORD imageBase, DWORD sizeOfImage);
VOID InsertListModule(HWND hWnd, int index, TCHAR* szModuleName, DWORD virtualAddress);
VOID EnumProcesses(HWND hWnd);
VOID EnumModules(HWND hWnd, DWORD pid);
VOID GetModuleInfo(DWORD pid, DWORD *imageBase, DWORD *sizeOfImage);
VOID OnOpenAddShell(HWND hWnd);
VOID OnOpenInject(HWND hWnd);
