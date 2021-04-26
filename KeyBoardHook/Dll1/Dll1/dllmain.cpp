// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"
#include <windows.h>
#include <ctime>
#include <cstdio>
#include <cstring>
#include <string>
#include <mmstream.h>
#include<Mmsystem.h>
#pragma comment(lib,"winmm.lib")
#define DLLEX extern "C" __declspec(dllexport) 
HMODULE hMod;
HHOOK hook;
int cnt = 1;
clock_t pre;
clock_t now;
double t;
LRESULT CALLBACK Proc(int code, WPARAM wParam, LPARAM lParam) {
	if (lParam & 0x80000000) {
		now=clock();
		t = (double)(now - pre) / CLOCKS_PER_SEC;
		if (t <= 0.2) {  return CallNextHookEx(hook, code, wParam, lParam); }
		std::string dir = "play ./music/";
		std::string ok = dir + (char)(cnt + '0');
		ok += ".mp3";
		mciSendString(ok.c_str(), 0, 0, 0);
		cnt++;
		if (cnt >= 8) cnt = 1;
		pre = now;
	}
	return CallNextHookEx(hook, code, wParam, lParam);
}
DLLEX void Start() {
	hook=SetWindowsHookEx(WH_KEYBOARD, Proc, hMod, 0);
	std::string dir = "open ./music/";
	for (int i = 1; i <= 7; i++) {
		std::string ok = dir + (char)(i + '0');
		ok += ".mp3";
		mciSendString(ok.c_str(), 0, 0, 0);
	}
}
DLLEX void Stop() {
	std::string dir = "close ./music/";
	for (int i = 1; i <= 7; i++) {
		std::string ok = dir + (char)(i + '0');
		ok += ".mp3";
		mciSendString(ok.c_str(), 0, 0, 0);
	}
	if (hook) {
		UnhookWindowsHookEx(hook);
		hook = 0;
	}
}
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
		hMod = hModule;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

