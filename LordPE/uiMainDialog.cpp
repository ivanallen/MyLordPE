#include "uiMainDialog.h"
#include "uiPEDialog.h"
#include "uiShellDialog.h"
#include "uiInjectDialog.h"
#include <tchar.h>


HPE pe = 0;
BOOL CALLBACK DialogMainProc( HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	switch(uMsg)
	{
	case WM_INITDIALOG:
		OnInitDialogMain(hwndDlg);	
		return TRUE;

	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case IDC_BUTTON_OPEN_PE:
			OnOpenPeButtonClicked(hwndDlg);
			break;
		case IDC_BUTTON_ADD_SHELL:
			OnOpenAddShell(hwndDlg);
			break;
		case IDC_BUTTON_INJECT:
			OnOpenInject(hwndDlg);
			break;
		case IDC_BUTTON_EXIT:
			EndDialog(hwndDlg, 0);
			break;
		}
		return TRUE;
	case WM_NOTIFY:
		{
			NMHDR* pNMHDR = (NMHDR*)lParam;
			if (wParam == IDC_LIST_PROCESS && pNMHDR->code == NM_CLICK)
			{
				OnListProcessClicked(hwndDlg, wParam, lParam);
			}
		}
		return TRUE;
	case WM_CLOSE:
		EndDialog(hwndDlg, 0);
		return TRUE;
	}
	return FALSE;
}



VOID InitListProcess(HWND hWnd)
{
	SendMessage(hWnd, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
	LVCOLUMN lvColumn = {0};
	lvColumn.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
	lvColumn.pszText = TEXT("进程");
	lvColumn.cx = 200;
	lvColumn.iSubItem = 0;
	ListView_InsertColumn(hWnd, 0, &lvColumn);

	lvColumn.pszText = TEXT("PID");
	lvColumn.cx = 100;
	lvColumn.iSubItem = 1;
	ListView_InsertColumn(hWnd, 1, &lvColumn);

	lvColumn.pszText = TEXT("镜像地址");
	lvColumn.cx = 100;
	lvColumn.iSubItem = 2;
	ListView_InsertColumn(hWnd, 2, &lvColumn);

	lvColumn.pszText = TEXT("镜像大小");
	lvColumn.cx = 100;
	lvColumn.iSubItem = 3;
	ListView_InsertColumn(hWnd, 3, &lvColumn);

}

VOID OnInitDialogMain( HWND hWnd )
{
	HICON hIcon = LoadIcon(hAppInstance, MAKEINTRESOURCE(IDI_ICON_MAIN));
	SendMessage(hWnd, WM_SETICON, ICON_BIG, (DWORD)hIcon);
	SendMessage(hWnd, WM_SETICON, ICON_SMALL, (DWORD)hIcon);
	CenterWindow(hWnd);
	HWND hListProcess = GetDlgItem(hWnd, IDC_LIST_PROCESS);
	HWND hListModule = GetDlgItem(hWnd, IDC_LIST_MODULE);
	InitListProcess(hListProcess);
	InitListModule(hListModule);
	EnumProcesses(hListProcess);
	
}

VOID InitListModule( HWND hWnd )
{
	LVCOLUMN lvColumn = {0};
	lvColumn.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
	lvColumn.pszText = TEXT("模块名称");
	lvColumn.cx = 200;
	lvColumn.iSubItem = 0;
	ListView_InsertColumn(hWnd, 0, &lvColumn);

	lvColumn.pszText = TEXT("模块位置");
	lvColumn.cx = 300;
	lvColumn.iSubItem = 1;
	ListView_InsertColumn(hWnd, 1, &lvColumn);
}

void OnOpenPeButtonClicked( HWND hWnd)
{
	TCHAR szPeFileExt[64] = TEXT("*.exe;*.dll;*.scr;*.drv;*.sys");
	TCHAR szFileName[MAX_PATH] = {0};
	OpenFileWindow(hWnd, szPeFileExt, szFileName, MAX_PATH);
	USES_CONVERSION;
	pe = loadPE(T2A(szFileName));
	if (!pe)
	{
		MessageBox(hWnd, TEXT("无效的PE文件！"), 0, 0);
		return;
	}
	DialogBox(hAppInstance, MAKEINTRESOURCE(IDD_DIALOG_PE), hWnd, DialogPEProc);
}

VOID InsertListProcess( HWND hWnd, int index, TCHAR* szProcessName, DWORD pid, DWORD imageBase, DWORD sizeOfImage )
{

	TCHAR buffer[64] = {0};
	LV_ITEM lvItem = {0};
	lvItem.mask = LVIF_TEXT;
	lvItem.pszText = szProcessName;
	lvItem.iItem = index;
	lvItem.iSubItem = 0;
	ListView_InsertItem(hWnd, &lvItem);

	stprintf(buffer, 64, TEXT("%d"), pid);
	lvItem.pszText = buffer;
	lvItem.iItem = index;
	lvItem.iSubItem = 1;
	ListView_SetItem(hWnd, &lvItem);

	stprintf(buffer, 64, TEXT("%08X"), imageBase);
	lvItem.pszText = buffer;
	lvItem.iItem = index;
	lvItem.iSubItem = 2;
	ListView_SetItem(hWnd, &lvItem);

	stprintf(buffer, 64, TEXT("%08X"), sizeOfImage);
	lvItem.pszText = buffer;
	lvItem.iItem = index;
	lvItem.iSubItem = 3;
	ListView_SetItem(hWnd, &lvItem);
}

VOID InsertListModule( HWND hWnd, int index, TCHAR* szModuleName, DWORD virtualAddress )
{
	TCHAR buffer[64] = {0};
	LV_ITEM lvItem = {0};
	lvItem.mask = LVIF_TEXT;
	lvItem.pszText = szModuleName;
	lvItem.iItem = index;
	lvItem.iSubItem = 0;
	ListView_InsertItem(hWnd, &lvItem);

	stprintf(buffer, 64, TEXT("%08X"), virtualAddress);
	lvItem.pszText = buffer;
	lvItem.iItem = index;
	lvItem.iSubItem = 1;
	ListView_SetItem(hWnd, &lvItem);

}

VOID EnumProcesses( HWND hWnd )
{
	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(pe32);
	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE)
	{
		return;
	}
	BOOL bResult = Process32First(hProcessSnap, &pe32);
	int i = 0;
	while (bResult)
	{
		TCHAR *szProcessName = pe32.szExeFile;
		DWORD pid = pe32.th32ProcessID;
		DWORD imageBase = 0;
		DWORD sizeOfImage = 0;
		GetModuleInfo(pid, &imageBase, &sizeOfImage);
		InsertListProcess(hWnd, i++, szProcessName, pid, imageBase, sizeOfImage);
		bResult = Process32Next(hProcessSnap, &pe32);
	}
	CloseHandle(hProcessSnap);
}

VOID EnumModules( HWND hWnd, DWORD pid )
{
	HANDLE hModuleSnap = INVALID_HANDLE_VALUE;
	MODULEENTRY32 me32;

	hModuleSnap = CreateToolhelp32Snapshot( TH32CS_SNAPMODULE, pid );
	if( hModuleSnap == INVALID_HANDLE_VALUE )
	{
		return;
	}

	me32.dwSize = sizeof( MODULEENTRY32 );

	if( !Module32First( hModuleSnap, &me32 ) )
	{
		CloseHandle( hModuleSnap );  
		return;
	}

	int i = 0;
	do
	{
		TCHAR* szModuleName = me32.szModule;
		DWORD virtualAddress = (DWORD)me32.modBaseAddr;
		InsertListModule(hWnd, i++, szModuleName, virtualAddress);
	} while( Module32Next( hModuleSnap, &me32 ) );

	CloseHandle( hModuleSnap );
}

VOID GetModuleInfo( DWORD pid, DWORD *imageBase, DWORD *sizeOfImage )
{
	HANDLE hModuleSnap = INVALID_HANDLE_VALUE;
	MODULEENTRY32 me32;

	hModuleSnap = CreateToolhelp32Snapshot( TH32CS_SNAPMODULE, pid );
	if( hModuleSnap == INVALID_HANDLE_VALUE )
	{
		return;
	}

	me32.dwSize = sizeof( MODULEENTRY32 );

	if( !Module32First( hModuleSnap, &me32 ) )
	{
		CloseHandle( hModuleSnap );  
		return;
	}


	*imageBase = (DWORD)me32.modBaseAddr;
	*sizeOfImage = me32.modBaseSize;

}
VOID OnListProcessClicked( HWND hWnd, WPARAM wParam, LPARAM lParam ) 
{
	HWND hListProcess = GetDlgItem(hWnd, IDC_LIST_PROCESS);
	HWND hListModule = GetDlgItem(hWnd, IDC_LIST_MODULE);
	NMITEMACTIVATE* pNmLVDISPINFO = (NMITEMACTIVATE*)lParam;
	TCHAR buffer[16] = {0};
	ListView_GetItemText(hListProcess, pNmLVDISPINFO->iItem, 1, buffer, 16);
	DWORD pid = _ttoi(buffer);
	ListView_DeleteAllItems(hListModule);
	EnumModules(hListModule, pid);
	
	return;
}

VOID OnOpenAddShell(HWND hWnd)
{
	DialogBox(hAppInstance, MAKEINTRESOURCE(IDD_DIALOG_SHELL), hWnd, DialogShellProc);
}

VOID OnOpenInject(HWND hWnd)
{
	DialogBox(hAppInstance, MAKEINTRESOURCE(IDD_DIALOG_INJECT), hWnd, DialogInjectProc);
}