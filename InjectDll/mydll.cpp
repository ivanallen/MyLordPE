#include "StdAfx.h"
#include "mydll.h"
#include <windows.h>


void init()
{
	MessageBox(0, "Init", "Init", MB_OK);
}

void destroy()
{
	MessageBox(0, "Destroy", "Destroy", MB_OK);
}

void exportFunction()
{
	MessageBox(0, "ExportFunction", "ExportFunction", MB_OK);
}
