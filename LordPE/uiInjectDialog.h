#pragma once

#include "Common.h"
BOOL CALLBACK DialogInjectProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void OnOpenModule(HWND hWnd);
void OnOpenFile(HWND hWnd);
void OnInject(HWND hWnd);
int GetCheckedRadioButton(HWND hWnd, int nIdFirstButton, int nIdLastButton);
void RemoteThreadInject(HWND hWnd);