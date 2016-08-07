#include "uiSectionDialog.h"

BOOL CALLBACK DialogSectionProc( HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	switch(uMsg)
	{
	case WM_INITDIALOG:
		OnInitDialogSection(hwndDlg);	
		return TRUE;
	case WM_CLOSE:
		EndDialog(hwndDlg, 0);
		return TRUE;
	}
	return FALSE;
}


VOID OnInitDialogSection( HWND hWnd ) 
{
	HWND hListSection = GetDlgItem(hWnd, IDC_LIST_SECTION);
	InitListSection(hListSection);
	IMAGE_SECTION_HEADER* pSectionHeaderBase = getSectionBase(pe);
	IMAGE_FILE_HEADER* pPEHeader = getFileHeader(pe);

	for (int i = 0; i < pPEHeader->NumberOfSections; ++i)
	{
		char* name = (char*)pSectionHeaderBase[i].Name;
		char buffer[16] = {0};
		sprintf_s(buffer, 9, "%s", name);
		DWORD sizeOfRawData = pSectionHeaderBase[i].SizeOfRawData;
		DWORD virtualSize = pSectionHeaderBase[i].Misc.VirtualSize;
		DWORD virtualAddress = pSectionHeaderBase[i].VirtualAddress;
		DWORD pointerToRawData = pSectionHeaderBase[i].PointerToRawData;
		DWORD characteristics = pSectionHeaderBase[i].Characteristics;
		USES_CONVERSION;
		InsertListSection(hListSection, i, A2T(buffer), pointerToRawData, sizeOfRawData, virtualAddress, virtualSize, characteristics);
	}
}

VOID InitListSection( HWND hWnd )
{
	SendMessage(hWnd, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
	LVCOLUMN lvColumn = {0};
	lvColumn.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
	lvColumn.pszText = TEXT("节名");
	lvColumn.cx = 80;
	lvColumn.iSubItem = 0;
	ListView_InsertColumn(hWnd, 0, &lvColumn);

	lvColumn.pszText = TEXT("文件偏移");
	lvColumn.cx = 80;
	lvColumn.iSubItem = 1;
	ListView_InsertColumn(hWnd, 1, &lvColumn);

	lvColumn.pszText = TEXT("文件大小");
	lvColumn.cx = 80;
	lvColumn.iSubItem = 2;
	ListView_InsertColumn(hWnd, 2, &lvColumn);

	lvColumn.pszText = TEXT("内存偏移");
	lvColumn.cx = 80;
	lvColumn.iSubItem = 3;
	ListView_InsertColumn(hWnd, 3, &lvColumn);

	lvColumn.pszText = TEXT("内存大小");
	lvColumn.cx = 80;
	lvColumn.iSubItem = 4;
	ListView_InsertColumn(hWnd, 4, &lvColumn);

	lvColumn.pszText = TEXT("节区属性");
	lvColumn.cx = 80;
	lvColumn.iSubItem = 5;
	ListView_InsertColumn(hWnd, 5, &lvColumn);

}

VOID InsertListSection( HWND hWnd, int index, TCHAR *szName, DWORD FOA, DWORD sizeOfRawData, DWORD RVA, DWORD virtualSize, DWORD characteristics )
{
	LV_ITEM lvItem = {0};
	lvItem.mask = LVIF_TEXT;
	lvItem.pszText = szName;
	lvItem.iItem = index;
	lvItem.iSubItem = 0;
	ListView_InsertItem(hWnd, &lvItem);

	TCHAR buffer[16] = {0};

	stprintf(buffer, 16, TEXT("%08X"), FOA);
	lvItem.pszText = buffer;
	lvItem.iItem = index;
	lvItem.iSubItem = 1;
	ListView_SetItem(hWnd, &lvItem);

	stprintf(buffer, 16, TEXT("%08X"), sizeOfRawData);
	lvItem.pszText = buffer;
	lvItem.iItem = index;
	lvItem.iSubItem = 2;
	ListView_SetItem(hWnd, &lvItem);

	stprintf(buffer, 16, TEXT("%08X"), RVA);
	lvItem.pszText = buffer;
	lvItem.iItem = index;
	lvItem.iSubItem = 3;
	ListView_SetItem(hWnd, &lvItem);

	stprintf(buffer, 16, TEXT("%08X"), virtualSize);
	lvItem.pszText = buffer;
	lvItem.iItem = index;
	lvItem.iSubItem = 4;
	ListView_SetItem(hWnd, &lvItem);

	stprintf(buffer, 16, TEXT("%08X"), characteristics);
	lvItem.pszText = buffer;
	lvItem.iItem = index;
	lvItem.iSubItem = 5;
	ListView_SetItem(hWnd, &lvItem);
}
