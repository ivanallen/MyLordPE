#include "uiDirectoryDialog.h"
#include "uiInfoDialog.h"

char szInfo[1024*512] = {0};
BOOL CALLBACK DialogDirectoryProc( HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	switch(uMsg)
	{
	case WM_INITDIALOG:
		OnInitDialogDirectory(hwndDlg);	
		return TRUE;
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case IDC_BUTTON_EXPORT:
			OnExportButtonClicked(hwndDlg);
			return TRUE;
		case IDC_BUTTON_IMPORT:
			OnImportButtonClicked(hwndDlg);
			return TRUE;
		case IDC_BUTTON_RESOURCE:
			OnResourceButtonClicked(hwndDlg);
			return TRUE;
		case IDC_BUTTON_RELOCATION:
			OnRelocationButtonClicked(hwndDlg);
			return TRUE;
		case IDC_BUTTON_BOUND_IMPORT:
			OnBoundImportButtonClicked(hwndDlg);
			return TRUE;
		case IDC_BUTTON_IAT:
			OnIATButtonClicked(hwndDlg);
			return TRUE;
		case IDC_BUTTON_CLOSE:
			EndDialog(hwndDlg, 0);
			break;
		}
		return TRUE;
	case WM_CLOSE:
		EndDialog(hwndDlg, 0);
		return TRUE;
	}
	return FALSE;
}

VOID OnInitDialogDirectory( HWND hWnd )
{
	if (!pe) return;

	IMAGE_OPTIONAL_HEADER32* pOptionalHeader = getOptionalHeader(pe);
	TCHAR buffer[16] = {0};

	for (int i = 0; i < pOptionalHeader->NumberOfRvaAndSizes; ++i)
	{
		stprintf(buffer, 16, TEXT("%08X"), pOptionalHeader->DataDirectory[i].VirtualAddress);
		SetWindowText(GetDlgItem(hWnd, IDC_EDIT1 + i), buffer);
		stprintf(buffer, 16, TEXT("%08X"), pOptionalHeader->DataDirectory[i].Size);
		SetWindowText(GetDlgItem(hWnd, IDC_EDIT1 + 16 + i), buffer);
	}
	
}

VOID OnExportButtonClicked( HWND hWnd )
{
	if(!pe) return;
	showmethod = SHOWEXPORT;
	DialogBox(hAppInstance, MAKEINTRESOURCE(IDD_DIALOG_INFO), hWnd, DialogInfoProc);
}

VOID OnImportButtonClicked( HWND hWnd )
{
	if(!pe) return;
	showmethod = SHOWIMPORT;
	DialogBox(hAppInstance, MAKEINTRESOURCE(IDD_DIALOG_INFO), hWnd, DialogInfoProc);
}

VOID OnResourceButtonClicked( HWND hWnd )
{
	if(!pe) return;
	showmethod = SHOWRESOURCE;
	DialogBox(hAppInstance, MAKEINTRESOURCE(IDD_DIALOG_INFO), hWnd, DialogInfoProc);
}

VOID OnRelocationButtonClicked( HWND hWnd )
{
	if(!pe) return;
	showmethod = SHOWRELOCATION;
	DialogBox(hAppInstance, MAKEINTRESOURCE(IDD_DIALOG_INFO), hWnd, DialogInfoProc);
}

VOID OnBoundImportButtonClicked( HWND hWnd )
{
	if(!pe) return;
	showmethod = SHOWBOUNDIMPORT;
	DialogBox(hAppInstance, MAKEINTRESOURCE(IDD_DIALOG_INFO), hWnd, DialogInfoProc);
}

VOID OnIATButtonClicked( HWND hWnd )
{
	//if(!pe) return;
	//showmethod = SHOWIAT;
	//DialogBox(hAppInstance, MAKEINTRESOURCE(IDD_DIALOG_INFO), hWnd, DialogInfoProc);
	OnImportButtonClicked(hWnd);
}
