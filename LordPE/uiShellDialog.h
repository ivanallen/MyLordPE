#pragma once
#include "Common.h"
BOOL CALLBACK DialogShellProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void OnButtonAddShell(HWND hWnd);
void OnButtonAddObject(HWND hWnd);
void OnGenerate(HWND hWnd);