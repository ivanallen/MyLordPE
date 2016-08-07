#include "uiInfoDialog.h"


int showmethod = SHOWNOTHING;
BOOL CALLBACK DialogInfoProc( HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	switch(uMsg)
	{
	case WM_INITDIALOG:
		OnInitDialogInfo(hwndDlg);	
		return TRUE;
	case WM_CLOSE:
		EndDialog(hwndDlg, 0);
		return TRUE;
	}
	return FALSE;
}

VOID OnInitDialogInfo( HWND hWnd )
{
	HWND hRichEdit = GetDlgItem(hWnd, IDC_RICHEDIT_INFO);
	switch(showmethod)
	{
	case SHOWEXPORT:
		ShowExport(hRichEdit);
		break;
	case SHOWIMPORT:
		ShowImport(hRichEdit);
		break;
	case SHOWRESOURCE:
		ShowResource(hRichEdit);
		break;
	case SHOWRELOCATION:
		ShowRelocation(hRichEdit);
		break;
	case SHOWBOUNDIMPORT:
		ShowBoundImport(hRichEdit);
		break;
	case SHOWIAT:
		ShowIAT(hRichEdit);
		break;
	}
}

VOID AppendTextToRichEdit( HWND hWnd, char* szText )
{
	SETTEXTEX stex = { ST_SELECTION, CP_ACP };
	SendMessage(hWnd, EM_SETTEXTEX, (WPARAM)&stex, (LPARAM)szText);
}

VOID ShowExport( HWND hWnd )
{
	if(!pe) return;
	char szInfo[1024] = {0};
	BYTE* fileBuffer = getFileBuffer(pe);
	IMAGE_EXPORT_DIRECTORY* pExportDirectory = getExportDirectory(pe);
	if (!pExportDirectory)
	{
		return;
	}
	sprintf(szInfo, "************************IMAGE_EXPORT_DIRECTORY************************\n"); 
	AppendTextToRichEdit(hWnd, szInfo); memset(szInfo, 0, 1024);
	sprintf(szInfo, "%-20s\t%08X\n", "时间戳: ", pExportDirectory->TimeDateStamp);
	AppendTextToRichEdit(hWnd, szInfo); memset(szInfo, 0, 1024);
	sprintf(szInfo, "%-20s\t%s\n", "模块名: ", (char*)(RVA2FOA(pe, pExportDirectory->Name)+(int)fileBuffer)); 
	AppendTextToRichEdit(hWnd, szInfo); memset(szInfo, 0, 1024);
	sprintf(szInfo, "%-20s\t%08X\n", "起始序号: ", pExportDirectory->Base); 
	AppendTextToRichEdit(hWnd, szInfo); memset(szInfo, 0, 1024);
	sprintf(szInfo, "%-20s\t%08X\n", "函数个数: ", pExportDirectory->NumberOfFunctions); 
	AppendTextToRichEdit(hWnd, szInfo); memset(szInfo, 0, 1024);
	sprintf(szInfo, "%-20s\t%08X\n", "函数名个数: ", pExportDirectory->NumberOfNames); 
	AppendTextToRichEdit(hWnd, szInfo); memset(szInfo, 0, 1024);
	sprintf(szInfo, "%-20s\t%08X\n", "函数地址表: ", pExportDirectory->AddressOfFunctions); 
	AppendTextToRichEdit(hWnd, szInfo); memset(szInfo, 0, 1024);
	sprintf(szInfo, "%-20s\t%08X\n", "名称地址表: ", pExportDirectory->AddressOfNames); 
	AppendTextToRichEdit(hWnd, szInfo); memset(szInfo, 0, 1024);
	sprintf(szInfo, "%-20s\t%08X\n\n", "序号地址表: ", pExportDirectory->AddressOfNameOrdinals); 
	AppendTextToRichEdit(hWnd, szInfo); memset(szInfo, 0, 1024);

	int* functionNames = (int*)(RVA2FOA(pe, pExportDirectory->AddressOfNames) + (int)fileBuffer);
	short* functionOrdinals = (short*)(RVA2FOA(pe, pExportDirectory->AddressOfNameOrdinals) + (int)fileBuffer);
	int* functionAddresses = (int*)(RVA2FOA(pe, pExportDirectory->AddressOfFunctions) + (int)fileBuffer);

	sprintf(szInfo, "%-45s\t%-10s\t%-10s\t%-10s\n", "函数名", "序号", "RVA", "FOA"); 
	AppendTextToRichEdit(hWnd, szInfo); memset(szInfo, 0, 1024);

	for (int i = 0; i < pExportDirectory->NumberOfNames; ++i)
	{
		sprintf(szInfo, "%-40s\t", (char*)(RVA2FOA(pe, functionNames[i]))+(int)fileBuffer); 
		AppendTextToRichEdit(hWnd, szInfo); memset(szInfo, 0, 1024);

		sprintf(szInfo, "%08X\t", functionOrdinals[i]); 
		AppendTextToRichEdit(hWnd, szInfo); memset(szInfo, 0, 1024);

		sprintf(szInfo, "%08X\t", functionAddresses[functionOrdinals[i]]); 
		AppendTextToRichEdit(hWnd, szInfo); memset(szInfo, 0, 1024);

		sprintf(szInfo, "%08X\n", RVA2FOA(pe, functionAddresses[functionOrdinals[i]]));
		AppendTextToRichEdit(hWnd, szInfo); memset(szInfo, 0, 1024);

	}
}

VOID ShowImport( HWND hWnd )
{
	if(!pe) return;
	char szInfo[1024] = {0};
	IMAGE_IMPORT_DESCRIPTOR* pImportDescriptor = getImportDescriptor(pe);
	if (!pImportDescriptor)
	{
		return;
	}
	BYTE* fileBuffer = getFileBuffer(pe);

	while ((pImportDescriptor->OriginalFirstThunk | pImportDescriptor->TimeDateStamp | pImportDescriptor->ForwarderChain | pImportDescriptor->Name | pImportDescriptor->FirstThunk ) != 0)
	{
		sprintf(szInfo, "----------------------------------------------------------------------------------------------------\n");
		AppendTextToRichEdit(hWnd, szInfo); memset(szInfo, 0, 1024);
		sprintf(szInfo, "模块名称: %s\n", (char*)(RVA2FOA(pe, pImportDescriptor->Name) + (int)fileBuffer));
		AppendTextToRichEdit(hWnd, szInfo); memset(szInfo, 0, 1024);

		if (pImportDescriptor->OriginalFirstThunk != 0)
		{
			int* originalFirstThunk = (int*)(RVA2FOA(pe, pImportDescriptor->OriginalFirstThunk) + (int)fileBuffer); 
			sprintf(szInfo, "|-- INT表\n");
			AppendTextToRichEdit(hWnd, szInfo); memset(szInfo, 0, 1024);
			while(*originalFirstThunk != 0)
			{
				if ((*originalFirstThunk & 0x80000000) == 0)
				{
					IMAGE_IMPORT_BY_NAME* name = (IMAGE_IMPORT_BY_NAME*)(RVA2FOA(pe, *originalFirstThunk) + (int)fileBuffer);
					sprintf(szInfo, "\t|-- HINT: %d, 函数名: %s\n", name->Hint, (char*)name->Name);
					AppendTextToRichEdit(hWnd, szInfo); memset(szInfo, 0, 1024);
				}
				else
				{
					 sprintf(szInfo, "\t|-- 以序号导入: %d\n", *originalFirstThunk & 0x7FFFFFFF);
					 AppendTextToRichEdit(hWnd, szInfo); memset(szInfo, 0, 1024);
				}

				++originalFirstThunk;
			}
		}
		else
		{
			sprintf(szInfo, "|-- INT表(空)\n");
			AppendTextToRichEdit(hWnd, szInfo); memset(szInfo, 0, 1024);
		}


		int* firstThunk = (int*)(RVA2FOA(pe, pImportDescriptor->FirstThunk) + (int)fileBuffer); 
		sprintf(szInfo, "|-- IAT表\n");
		AppendTextToRichEdit(hWnd, szInfo); memset(szInfo, 0, 1024);
		while(*firstThunk != 0)
		{
			if ((*firstThunk & 0x80000000) == 0)
			{
				IMAGE_IMPORT_BY_NAME* name = (IMAGE_IMPORT_BY_NAME*)(RVA2FOA(pe, *firstThunk) + (int)fileBuffer);
				if (!pImportDescriptor->TimeDateStamp)
				{
					sprintf(szInfo, "\t|-- HINT: %d, 函数名(未绑定): %s\n", name->Hint, (char*)name->Name);
					AppendTextToRichEdit(hWnd, szInfo); memset(szInfo, 0, 1024);
				}
				else
				{
					sprintf(szInfo, "\t|-- 函数已绑定地址: %X\n", *firstThunk);
					AppendTextToRichEdit(hWnd, szInfo); memset(szInfo, 0, 1024);
				}

			}
			else
			{
				sprintf(szInfo, "\t|-- 以序号导入: %d\n", *firstThunk & 0x7FFFFFFF);
			}

			++firstThunk;
		}
		++pImportDescriptor;
	}
}

VOID ShowResource( HWND hWnd )
{
	if(!pe) return;
	char szInfo[1024] = {0};
	char *resourceType[] = {"", "光标", "位图", "图标", "菜单", "对话框", "字串表", "字体目录" , "字体" ,  "加速键", "未格式化资源" , "消息表" , "光标组" , "" , "图标组" ,  "" , "版本信息"};
	BYTE* filebuffer = getFileBuffer(pe);
	IMAGE_RESOURCE_DIRECTORY* pResourceDirectory = getResourceDirectory(pe);

	if (!pResourceDirectory)
	{
		return;
	}
	// level 1
	IMAGE_RESOURCE_DIRECTORY* pResourceType = pResourceDirectory;
	IMAGE_RESOURCE_DIRECTORY_ENTRY* pResourceEntry1 = (IMAGE_RESOURCE_DIRECTORY_ENTRY*)(pResourceType + 1);

	for (int i = 0; i < pResourceDirectory->NumberOfIdEntries + pResourceDirectory->NumberOfNamedEntries; ++i)
	{

		if (pResourceEntry1[i].NameIsString == 1)
		{
			IMAGE_RESOURCE_DIR_STRING_U* str = (IMAGE_RESOURCE_DIR_STRING_U*)((int)pResourceType + pResourceEntry1[i].NameOffset);
			WCHAR buffer[256] = {0};
			getString(str, buffer, 256);
			USES_CONVERSION;
			sprintf(szInfo, "|-- %s\n", W2A(buffer));
			AppendTextToRichEdit(hWnd, szInfo); memset(szInfo, 0, 1024);
		}
		else
		{
			if (pResourceEntry1[i].Id <= 16)
			{
				sprintf(szInfo, "|-- %s\n", resourceType[pResourceEntry1[i].Id]);
				AppendTextToRichEdit(hWnd, szInfo); memset(szInfo, 0, 1024);
			}
			else
			{
				sprintf(szInfo, "|-- %d\n", pResourceEntry1[i].Id);
				AppendTextToRichEdit(hWnd, szInfo); memset(szInfo, 0, 1024);
			}
		}
		// level 2
		IMAGE_RESOURCE_DIRECTORY* pResourceID = (IMAGE_RESOURCE_DIRECTORY*)((int)pResourceType + pResourceEntry1[i].OffsetToDirectory);
		IMAGE_RESOURCE_DIRECTORY_ENTRY* pResourceEntry2 = (IMAGE_RESOURCE_DIRECTORY_ENTRY*)(pResourceID + 1);
		for (int j = 0; j < pResourceID->NumberOfIdEntries + pResourceID->NumberOfNamedEntries; ++j)
		{
			if (pResourceEntry2[j].NameIsString == 1)
			{
				IMAGE_RESOURCE_DIR_STRING_U* str = (IMAGE_RESOURCE_DIR_STRING_U*)((int)pResourceType + pResourceEntry2[j].NameOffset);
				WCHAR buffer[256] = {0};
				getString(str, buffer, 256);
				USES_CONVERSION;
				sprintf(szInfo, "\t|-- %s\n", W2A(buffer));
				AppendTextToRichEdit(hWnd, szInfo); memset(szInfo, 0, 1024);
			}
			else
			{				
				sprintf(szInfo, "\t|-- %d\n", pResourceEntry2[j].Id);	
				AppendTextToRichEdit(hWnd, szInfo); memset(szInfo, 0, 1024);
			}

			// level 3
			IMAGE_RESOURCE_DIRECTORY* pResourceCodePage = (IMAGE_RESOURCE_DIRECTORY*)((int)pResourceType + pResourceEntry2[j].OffsetToDirectory);
			IMAGE_RESOURCE_DIRECTORY_ENTRY* pResourceEntry3 = (IMAGE_RESOURCE_DIRECTORY_ENTRY*)(pResourceCodePage + 1);
			for (int k = 0; k < pResourceCodePage->NumberOfIdEntries + pResourceCodePage->NumberOfNamedEntries; ++k)
			{
				if (pResourceEntry3[k].NameIsString == 1)
				{
					IMAGE_RESOURCE_DIR_STRING_U* str = (IMAGE_RESOURCE_DIR_STRING_U*)((int)pResourceType + pResourceEntry3[k].NameOffset);
					WCHAR buffer[256] = {0};
					getString(str, buffer, 256);
					USES_CONVERSION;
					sprintf(szInfo, "\t\t|-- %s", W2A(buffer));
					AppendTextToRichEdit(hWnd, szInfo); memset(szInfo, 0, 1024);
				}
				else
				{				
					sprintf(szInfo, "\t\t|-- %d", pResourceEntry3[k].Id);	
					AppendTextToRichEdit(hWnd, szInfo); memset(szInfo, 0, 1024);
				}

				IMAGE_DATA_DIRECTORY* data = (IMAGE_DATA_DIRECTORY*)((int)pResourceType + pResourceEntry3[k].OffsetToData);
				sprintf(szInfo, "\tRVA: %08X Size: %d\n", data->VirtualAddress, data->Size);
				AppendTextToRichEdit(hWnd, szInfo); memset(szInfo, 0, 1024);
				//printf("\n");
			}
		}
	}
}

VOID ShowRelocation( HWND hWnd )
{
	if(!pe) return;
	BYTE* fileBuffer = getFileBuffer(pe);
	char szInfo[1024] = {0};
	IMAGE_BASE_RELOCATION* pBaseRelocation = getRelocationDirectory(pe);
	if (!pBaseRelocation)
	{
		return;
	}
	int offset = 0;
	while ((pBaseRelocation->VirtualAddress | pBaseRelocation->SizeOfBlock) != 0)
	{
		sprintf(szInfo, "----------------------------------------------------------------------------------------------------------------\n");
		AppendTextToRichEdit(hWnd, szInfo); memset(szInfo, 0, 1024);
		sprintf(szInfo, "镜像基地址: %08X\n", pBaseRelocation->VirtualAddress);
		AppendTextToRichEdit(hWnd, szInfo); memset(szInfo, 0, 1024);
		short* pTable = (short*)((int)pBaseRelocation + 8);
		int len = (pBaseRelocation->SizeOfBlock - 8) / 2;
		sprintf(szInfo, "\t|-- ID \t\tRVA \t\tFOA \t\tTYPE \tADDRESS \n");
		AppendTextToRichEdit(hWnd, szInfo); memset(szInfo, 0, 1024);
		for (int i = 0; i < len; ++i)
		{
			int RVA = pBaseRelocation->VirtualAddress + (pTable[i] & 0x0FFF);
			int FOA = RVA2FOA(pe, RVA);
			sprintf(szInfo, "\t|-- %05d \t%08X \t%08X \t%d \t", i, RVA, FOA, (pTable[i] & 0xF000) >> 12);
			AppendTextToRichEdit(hWnd, szInfo); memset(szInfo, 0, 1024);
			sprintf(szInfo, "%08X \n", *(int*)(FOA+ (int)fileBuffer));
			AppendTextToRichEdit(hWnd, szInfo); memset(szInfo, 0, 1024);
		}


		pBaseRelocation = (IMAGE_BASE_RELOCATION*)((int)pBaseRelocation + pBaseRelocation->SizeOfBlock);
	}
}

VOID ShowBoundImport( HWND hWnd )
{
	if(!pe) return;
	char szInfo[1024] = {0};

	IMAGE_BOUND_IMPORT_DESCRIPTOR* pBoundImportDescriptor = getBoundImportDescriptor(pe);
	if(!pBoundImportDescriptor)
	{
		//sprintf("绑定导入表不存在");
		return;
	}
	IMAGE_BOUND_IMPORT_DESCRIPTOR* pBoundImportDescriptorBak = pBoundImportDescriptor;
	BYTE* fileBuffer = getFileBuffer(pe);


	while (pBoundImportDescriptor->TimeDateStamp | pBoundImportDescriptor->OffsetModuleName | pBoundImportDescriptor->NumberOfModuleForwarderRefs != 0)
	{
		sprintf(szInfo, "|-- 名称：%s\t", (char*)(pBoundImportDescriptor->OffsetModuleName + (int)pBoundImportDescriptorBak));
		AppendTextToRichEdit(hWnd, szInfo); memset(szInfo, 0, 1024);
		sprintf(szInfo, "时间戳：%08X\n", pBoundImportDescriptor->TimeDateStamp);
		AppendTextToRichEdit(hWnd, szInfo); memset(szInfo, 0, 1024);
		for (int i = 1; i <= pBoundImportDescriptor->NumberOfModuleForwarderRefs; ++i)
		{
			sprintf(szInfo, "      |-- 名称：%s\t", (char*)(pBoundImportDescriptor[i].OffsetModuleName + (int)pBoundImportDescriptorBak));
			AppendTextToRichEdit(hWnd, szInfo); memset(szInfo, 0, 1024);
			sprintf(szInfo, "时间戳：%08X\n", pBoundImportDescriptor[i].TimeDateStamp);
			AppendTextToRichEdit(hWnd, szInfo); memset(szInfo, 0, 1024);
		}
		pBoundImportDescriptor += pBoundImportDescriptor->NumberOfModuleForwarderRefs + 1;
	}
}

VOID ShowIAT( HWND hWnd )
{
	//OnImportButtonClicked(hWnd);
}