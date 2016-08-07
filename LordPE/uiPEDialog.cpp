#include "uiPEDialog.h"
#include "uiSectionDialog.h"
#include "uiDirectoryDialog.h"

BOOL CALLBACK DialogPEProc( HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	switch(uMsg)
	{
	case WM_INITDIALOG:
		OnInitDialogPE(hwndDlg);	
		return TRUE;

	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case IDC_BUTTON_SECTION:
			OnSectionButtonClicked(hwndDlg);
			break;
		case IDC_BUTTON_DIRECTORY:
			OnDirectoryButtonClicked(hwndDlg);
			break;
		case IDC_BUTTON_CLOSE:
			if(pe)
			{
				releasePE(pe);
				pe = 0;
			}
			EndDialog(hwndDlg, 0);
			break;
		}
		return TRUE;
	case WM_CLOSE:
		if(pe)
		{
			releasePE(pe);
			pe = 0;
		}
		EndDialog(hwndDlg, 0);
		return TRUE;
	}
	return FALSE;
}

VOID OnInitDialogPE( HWND hWnd )
{
	if (pe != 0)
	{
		IMAGE_OPTIONAL_HEADER32* pOptionalHeader = getOptionalHeader(pe);
		IMAGE_FILE_HEADER* pFileHeader = getFileHeader(pe);

		TCHAR buffer[16] = {0};

		stprintf(buffer, 16, TEXT("%08X"), pOptionalHeader->AddressOfEntryPoint);
		SetWindowText(GetDlgItem(hWnd, IDC_EDIT1), buffer);

		stprintf(buffer, 16, TEXT("%08X"), pOptionalHeader->ImageBase);
		SetWindowText(GetDlgItem(hWnd, IDC_EDIT2), buffer);

		stprintf(buffer, 16, TEXT("%08X"), pOptionalHeader->SizeOfImage);
		SetWindowText(GetDlgItem(hWnd, IDC_EDIT3), buffer);

		stprintf(buffer, 16, TEXT("%08X"), pOptionalHeader->BaseOfCode);
		SetWindowText(GetDlgItem(hWnd, IDC_EDIT4), buffer);

		stprintf(buffer, 16, TEXT("%08X"), pOptionalHeader->BaseOfData);
		SetWindowText(GetDlgItem(hWnd, IDC_EDIT5), buffer);

		stprintf(buffer, 16, TEXT("%08X"), pOptionalHeader->SectionAlignment);
		SetWindowText(GetDlgItem(hWnd, IDC_EDIT6), buffer);

		stprintf(buffer, 16, TEXT("%08X"), pOptionalHeader->FileAlignment);
		SetWindowText(GetDlgItem(hWnd, IDC_EDIT7), buffer);

		stprintf(buffer, 16, TEXT("%04X"), pOptionalHeader->Magic);
		SetWindowText(GetDlgItem(hWnd, IDC_EDIT8), buffer);

		stprintf(buffer, 16, TEXT("%04X"), pOptionalHeader->Subsystem);
		SetWindowText(GetDlgItem(hWnd, IDC_EDIT9), buffer);

		stprintf(buffer, 16, TEXT("%04X"), pFileHeader->NumberOfSections);
		SetWindowText(GetDlgItem(hWnd, IDC_EDIT10), buffer);

		stprintf(buffer, 16, TEXT("%08X"), pFileHeader->TimeDateStamp);
		SetWindowText(GetDlgItem(hWnd, IDC_EDIT11), buffer);

		stprintf(buffer, 16, TEXT("%08X"), pOptionalHeader->SizeOfHeaders);
		SetWindowText(GetDlgItem(hWnd, IDC_EDIT12), buffer);

		stprintf(buffer, 16, TEXT("%04X"), pFileHeader->Characteristics);
		SetWindowText(GetDlgItem(hWnd, IDC_EDIT13), buffer);

		stprintf(buffer, 16, TEXT("%08X"), pOptionalHeader->CheckSum);
		SetWindowText(GetDlgItem(hWnd, IDC_EDIT14), buffer);

		stprintf(buffer, 16, TEXT("%04X"), pFileHeader->SizeOfOptionalHeader);
		SetWindowText(GetDlgItem(hWnd, IDC_EDIT15), buffer);

		stprintf(buffer, 16, TEXT("%08X"), pOptionalHeader->NumberOfRvaAndSizes);
		SetWindowText(GetDlgItem(hWnd, IDC_EDIT16), buffer);
	}
}



VOID OnSectionButtonClicked( HWND hWnd )
{
	DialogBox(hAppInstance, MAKEINTRESOURCE(IDD_DIALOG_SECTION), hWnd, DialogSectionProc);
}

VOID OnDirectoryButtonClicked( HWND hWnd )
{
	DialogBox(hAppInstance, MAKEINTRESOURCE(IDD_DIALOG_DIRECTORY), hWnd, DialogDirectoryProc);
}
