#pragma once
#include <stdio.h>
#include <tchar.h>
#include <windows.h>
typedef int HPE;
typedef struct _PE{
	int length;
	BYTE* fileBuffer;
	IMAGE_DOS_HEADER* pDosHeader;
	IMAGE_NT_HEADERS* pNTHeaders;
	IMAGE_FILE_HEADER* pPEHeader;
	IMAGE_OPTIONAL_HEADER32* pOptionalHeader;
	IMAGE_SECTION_HEADER* pSectionHeader;
}PE;
extern char* FILENAME_IN;
extern char* FILENAME_OUT;


int readFile(IN const char* filename, OUT BYTE** buffer);


void writeFile(IN const char* filename, IN BYTE* data, IN int len);

void writeFile(IN const char* filename, IN HPE pe);

int initializePE(IN const BYTE* data, OUT IMAGE_DOS_HEADER** pDosHeader, OUT IMAGE_NT_HEADERS** pNTHeaders, OUT IMAGE_FILE_HEADER** pPEHeader, OUT IMAGE_OPTIONAL_HEADER32** pOptionalHeader, OUT IMAGE_SECTION_HEADER** pSectionHeader);


int fileBufferToImageBuffer(IN const BYTE* filebuffer, OUT BYTE** imagebuffer);


int imageBufferToFileBuffer(IN const BYTE* imagebuffer, OUT BYTE** filebuffer);


// 内存偏移地址转换为文件偏移地址
int RVA2FOA(IN HPE pe, IN int rva);

int FOA2RVA(IN const HPE pe, IN int foa);

IMAGE_SECTION_HEADER* getSectionHeader(IN HPE pe, IN int foa);

HPE loadPE(const char* filename);

HPE loadPEFromBuffer(IN const BYTE* buffer, IN int length);

void releasePE(HPE pe);

HPE  addSection(IN HPE pe, IN const char* sectionName, IN int sectionLength, IN int properties);

void moveExportDirectory(IN HPE pe, IN const char* sectionName);

void moveRelocationDirectory(IN HPE pe, IN const char* sectionName);

//返回新的导入表地址
IMAGE_IMPORT_DESCRIPTOR*  moveImportDescriptor(IN HPE pe, IN const char* sectionName);

void modifyRelocationDirectory(IN HPE pe, IN int imageBase);

IMAGE_IMPORT_DESCRIPTOR* getImportDescriptor(IN HPE pe);

IMAGE_BOUND_IMPORT_DESCRIPTOR* getBoundImportDescriptor(IN HPE pe);

IMAGE_RESOURCE_DIRECTORY* getResourceDirectory(IN HPE pe);

IMAGE_SECTION_HEADER* getSection(IN HPE pe, IN const char* sectionName);

IMAGE_SECTION_HEADER* getLastSection(IN HPE pe);

IMAGE_SECTION_HEADER* getSectionBase(IN HPE pe);

IMAGE_EXPORT_DIRECTORY* getExportDirectory(IN HPE pe);

IMAGE_BASE_RELOCATION* getRelocationDirectory(IN HPE pe);

int* getIATDirectory(IN HPE pe);

void importDescriptorInject(IN HPE pe, IN const IMAGE_IMPORT_DESCRIPTOR* pImportDescriptor, IN const char* moduleName, IN const char** functionNames, IN int length);

BYTE* getFileBuffer(IN HPE pe);

int getFileLength(IN HPE pe);

IMAGE_OPTIONAL_HEADER32* getOptionalHeader(IN HPE pe);

IMAGE_FILE_HEADER* getFileHeader(IN HPE pe);

void getString(IN const IMAGE_RESOURCE_DIR_STRING_U* str, OUT WCHAR* buffer, int length);

HPE protect(IN HPE shell, IN HPE obj);