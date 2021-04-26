#include<windows.h>
#include<cstdio>
#include<Mmstream.h>
#pragma comment(lib,"winmm.lib")
using namespace std;
typedef void(*Func)();
int APIENTRY wWinMain(HINSTANCE hInstance,HINSTANCE hPreInstance,LPTSTR lpCmdLine,int CmdShow) {
	Func START, STOP;
	HINSTANCE HDll;
	HDll=LoadLibrary(L"./Dll1.dll");
	START = (Func)GetProcAddress(HDll, "Start");
	STOP = (Func)GetProcAddress(HDll, "Stop");
	START();
	MessageBox(NULL, L"", L"", MB_OK);
	STOP();
	return 0;
                                      
}