﻿#include <Windows.h>


extern "C" __declspec(dllexport) void printStrLen(char* str) {
    char buf[15];
    sprintf(buf, "%d", strlen(str));
    WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), buf, strlen(buf), NULL, NULL);
}

BOOL APIENTRY DllMain(HMODULE /* hModule */, DWORD ul_reason_for_call, LPVOID /* lpReserved */)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
