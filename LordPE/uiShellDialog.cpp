#include "uiShellDialog.h"






BOOL CALLBACK DialogShellProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
		
		return TRUE;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON_SHELL_SRC:
			OnButtonAddShell(hwndDlg);
			break;
		case IDC_BUTTON_OBJ_SRC:
			OnButtonAddObject(hwndDlg);
			break;
		case IDC_BUTTON_GENERATE:
			OnGenerate(hwndDlg);
			break;
		}
		return TRUE;
	
		
	case WM_CLOSE:
		EndDialog(hwndDlg, 0);
		return TRUE;
	}
	return FALSE;
}


void OnButtonAddShell(HWND hWnd)
{
	TCHAR szPeFileExt[64] = TEXT("*.exe;*.dll;*.scr;*.drv;*.sys");
	TCHAR szFileName[MAX_PATH] = { 0 };
	OpenFileWindow(hWnd, szPeFileExt, szFileName, MAX_PATH);	
	SetWindowText(GetDlgItem(hWnd, IDC_EDIT_SHELL_SRC), szFileName);
	
}

void OnButtonAddObject(HWND hWnd)
{
	TCHAR szPeFileExt[64] = TEXT("*.exe;*.dll;*.scr;*.drv;*.sys");
	TCHAR szFileName[MAX_PATH] = { 0 };
	OpenFileWindow(hWnd, szPeFileExt, szFileName, MAX_PATH);
	SetWindowText(GetDlgItem(hWnd, IDC_EDIT_OBJ_SRC), szFileName);
}

void OnGenerate(HWND hWnd)
{
	char szShellCode[MAX_PATH] = { 0 };
	char szObjectCode[MAX_PATH] = { 0 };
	GetWindowTextA(GetDlgItem(hWnd, IDC_EDIT_SHELL_SRC), szShellCode, MAX_PATH);
	GetWindowTextA(GetDlgItem(hWnd, IDC_EDIT_OBJ_SRC), szObjectCode, MAX_PATH);
	HPE shell = loadPE(szShellCode);
	HPE obj = loadPE(szObjectCode);

	if (!shell || !obj)
	{
		MessageBoxA(hWnd, "文件加载失败\n", NULL, MB_ICONERROR);
		return;
	}

	int start = strlen(szObjectCode);
	while (start >=0 && szObjectCode[start] != '\\')
	{
		--start;
	}

	char newObjName[MAX_PATH] = { 0 };
	sprintf_s(newObjName, MAX_PATH, "P_%s", szObjectCode+start+1);

	HPE newObj = protect(shell, obj);
	writeFile(newObjName, newObj);
	releasePE(shell);
	releasePE(obj);
	releasePE(newObj);
	MessageBoxA(hWnd, "生成成功\n", NULL, MB_OK);
}