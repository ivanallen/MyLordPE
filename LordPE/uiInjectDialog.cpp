#include "uiInjectDialog.h"


BOOL CALLBACK DialogInjectProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:

		return TRUE;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON_MODULE:
			OnOpenModule(hWnd);
			break;
		case IDC_BUTTON_FILE:
			OnOpenFile(hWnd);
			break;
		case IDC_BUTTON_INJECT:
			OnInject(hWnd);
		}
		return TRUE;


	case WM_CLOSE:
		EndDialog(hWnd, 0);
		return TRUE;
	}
	return FALSE;
}


void OnOpenModule(HWND hWnd)
{
	TCHAR szFileName[MAX_PATH] = { 0 };
	TCHAR szPeFileExt[64] = TEXT("*.exe;*.dll;*.scr;*.drv;*.sys");
	OpenFileWindow(hWnd, szPeFileExt, szFileName, MAX_PATH);
	SetWindowText(GetDlgItem(hWnd, IDC_EDIT_MODULE), szFileName);
}

void OnOpenFile(HWND hWnd)
{
	TCHAR szFileName[MAX_PATH] = { 0 };
	TCHAR szPeFileExt[64] = TEXT("*.exe;*.dll;*.scr;*.drv;*.sys");
	OpenFileWindow(hWnd, szPeFileExt, szFileName, MAX_PATH);
	SetWindowText(GetDlgItem(hWnd, IDC_EDIT_FILE), szFileName);
}





void OnInject(HWND hWnd)
{
	int radio = GetCheckedRadioButton(hWnd, IDC_RADIO1, IDC_RADIO5);
	switch (radio)
	{
	case IDC_RADIO1:
		
		break;
	case IDC_RADIO2:
		RemoteThreadInject(hWnd);
		break;
	case IDC_RADIO3:
		break;
	case IDC_RADIO4:
		break;
	case IDC_RADIO5:
		break;
	}
}

int GetCheckedRadioButton(HWND hWnd, int nIdFirstButton, int nIdLastButton)
{
	for (int i = nIdFirstButton; i <= nIdLastButton; ++i)
	{
		if (BST_CHECKED == IsDlgButtonChecked(hWnd, i)) return i;
	}
}


void RemoteThreadInject(HWND hWnd)
{
	int pid = GetDlgItemInt(hWnd, IDC_EDIT_PID, NULL, TRUE);
	char szModuleName[MAX_PATH] = { 0 };
	GetWindowTextA(GetDlgItem(hWnd, IDC_EDIT_MODULE), szModuleName, MAX_PATH);
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
	LPVOID buffer = VirtualAllocEx(hProcess, NULL, strlen(szModuleName) + 1, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	if (!buffer) return;
	DWORD writenum = 0;
	WriteProcessMemory(hProcess, buffer, szModuleName, strlen(szModuleName) + 1, &writenum);
	HANDLE hThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)LoadLibraryA, buffer, 0, NULL);
	WaitForSingleObject(hThread, INFINITE);
	
	HMODULE hMoudle = NULL;
	GetExitCodeThread(hThread, (DWORD*)&hMoudle);
	CloseHandle(hThread);
	VirtualFreeEx(hProcess, buffer, strlen(szModuleName) + 1, MEM_RELEASE);
}