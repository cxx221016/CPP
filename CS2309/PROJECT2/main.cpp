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
	bi.lpszTitle = L"������";//�������û���ʾ��ʾ�ַ���
	bi.ulFlags = BIF_RETURNONLYFSDIRS |BIF_USENEWUI |BIF_BROWSEINCLUDEFILES;
	LPITEMIDLIST idl = SHBrowseForFolder(&bi);
	if (NULL == idl)
	{
		return;
	}
	SHGetPathFromIDList(idl, szBuffer);//���·��
	MessageBox(NULL, szBuffer, szBuffer, 0);//�����õ�·��
}
LRESULT CALLBACK WindowProc(
	HWND hwnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
) {
	switch (uMsg) {
	case WM_CLOSE:
		DestroyWindow(hwnd);//����һ����ϢWM_Destroy����ʾ���𴰿ڣ���������
		break;
	case WM_DESTROY:
		PostQuitMessage(0);//�������������˳�����Ϣ
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
	GetMoreFile();//���ļ�ѡ��ͼ�ν����Ի�ȡ�ļ�·��
	while (1) {
		if (GetMessage(&msg, NULL, 0, 0) == FALSE) {
			break;
		}
		//������Ϣ
		TranslateMessage(&msg);
		//�ַ���Ϣ
		DispatchMessage(&msg);
		Sleep(20);
	}
    system("pause");
	return 0;
}
