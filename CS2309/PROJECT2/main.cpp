#include <Windows.h>
#include <ShlObj.h>
#include<tchar.h>
#define X (200)
#define Y (200)
void GetMoreFile() 
{
	TCHAR szBuffer[MAX_PATH]{ 0 };
	BROWSEINFO bi;
	ZeroMemory(&bi, sizeof(BROWSEINFO));
	bi.hwndOwner = NULL;
	bi.pszDisplayName = szBuffer;
	bi.lpszTitle = L"请输入";//用以向用户显示提示字符串
	bi.ulFlags = BIF_RETURNONLYFSDIRS |BIF_USENEWUI |BIF_BROWSEINCLUDEFILES;
	LPITEMIDLIST idl = SHBrowseForFolder(&bi);
	if (NULL == idl)
	{
		return;
	}
	SHGetPathFromIDList(idl, szBuffer);//获得路径
	MessageBox(NULL, szBuffer, szBuffer, 0);//输出获得的路径
}
LRESULT CALLBACK WindowProc(
	HWND hwnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
) {
	switch (uMsg) {
	case WM_CLOSE:
		DestroyWindow(hwnd);//发送一个消息WM_Destroy，表示毁灭窗口，但程序还在
		break;
	case WM_DESTROY:
		PostQuitMessage(0);//发送正常程序退出的消息
		break;
	case WM_LBUTTONUP:
		DestroyWindow(hwnd);
		break;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
int WINAPI wWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPWSTR    lpCmdLine,
	int       nCmdShow)
{
	WNDCLASS wc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.hCursor = LoadCursor(NULL, IDC_HAND);
	wc.hIcon = LoadIcon(NULL, IDI_HAND);
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WindowProc;
	wc.lpszClassName = TEXT("WIN");
	wc.lpszMenuName = NULL;
	wc.style = 0;
	RegisterClass(&wc);
	HWND hwnd = CreateWindow(wc.lpszClassName, TEXT("WINDOWS"), wc.style, CW_USEDEFAULT, CW_USEDEFAULT, X, Y, NULL, NULL, hInstance, NULL);
	ShowWindow(hwnd, SW_SHOWNORMAL);
	UpdateWindow(hwnd);
	MSG msg;
	GetMoreFile();//打开文件选择图形界面以获取文件路径
	while (1) {
		if (GetMessage(&msg, NULL, 0, 0) == FALSE) {
			break;
		}
		//翻译消息
		TranslateMessage(&msg);
		//分发消息
		DispatchMessage(&msg);
		Sleep(20);
	}
    system("pause");
	return 0;
}
