// dllmain.cpp : Defines the entry point for the DLL application.
// NOTES:
// -x64 compilation needed so that 
#include "pch.h"
#include <iostream>

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
		std::cout << "DLL_PROCESS_ATTACH" << std::endl;
		break;

    case DLL_THREAD_ATTACH:
		std::cout << "DLL_THREAD_ATTACH" << std::endl;
		break;

	case DLL_THREAD_DETACH:
		std::cout << "DLL_THREAD_DETACH" << std::endl;
		break;

	case DLL_PROCESS_DETACH:
		std::cout << "DLL_PROCESS_DETACH" << std::endl;
		break;
    }
    return TRUE;
}

// extern "C" required so that C++ name mangling doesn't change the function
// signatures, making it unrecognisable to users of the DLL.
#ifdef __cplusplus
extern "C"
{
#endif
	__declspec(dllexport) void TestFunction1()
	{
		std::cout << "TestFunction1 called" << std::endl;
	}

	__declspec(dllexport) int TestFunction2(int param1)
	{
		return param1 * 2;
	}
#ifdef __cplusplus
}
#endif