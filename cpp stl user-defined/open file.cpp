#ifdef UNICODE
#undef UNICODE
#endif
 
#include "windows.h"
#include <stdlib.h>
#include <iostream>
#include <commdlg.h>
using namespace std;
 
int main(int argc, char *argv[])
{
	TCHAR szBuffer[MAX_PATH] = { 0 };
	OPENFILENAME file = { 0 };
	file.hwndOwner = NULL;
	file.lStructSize = sizeof(file);
	file.lpstrFilter = "所有文件(*.*)\0*.*\0Exe文件(*.exe)\0*.exe\0";//要选择的文件后缀 
	file.lpstrInitialDir = "";//默认的文件路径 
	file.lpstrFile = szBuffer;//存放文件的缓冲区 
	file.nMaxFile = sizeof(szBuffer) / sizeof(*szBuffer);
	file.nFilterIndex = 0;
	file.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_EXPLORER;//标志如果是多选要加上OFN_ALLOWMULTISELECT
	BOOL bSel = GetOpenFileName(&file);
	cout << file.lpstrFile << endl;
    system("pause");
	return (0);
}