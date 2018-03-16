// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"

BOOL checkDll();

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        //! check load and apis
        return  checkDll();

    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

const char *_apis[] =
{
    "OpenDevice",
    "CloseDevice",
    "InitCAN",
    "ReadBoardInfo",

    "ReadErrInfo",
    "ReadCANStatus",
    "GetReference",
    "SetReference",

    "GetReceiveNum",
    "ClearBuffer",
    "StartCAN",
    "ResetCAN",

    "Transmit",
    "Receive",
};

BOOL checkDll()
{
    HMODULE hDll = LoadLibrary("Ecanvci.dll");
    if (hDll == INVALID_HANDLE_VALUE)
    {
        return false;
    }

    //! load apis
    //GetProcAddress()
    for (int i = 0; i < sizeof(_apis) / sizeof(_apis[0]); i++)
    {
        if (NULL == GetProcAddress(hDll, _apis[i]))
        {
            return false;
        }
    }

    return true;
}