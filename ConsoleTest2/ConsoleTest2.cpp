/**
 * ConsoleTest2
 * ------------
 * An example of how an external DLL can be referenced at runtime.
 */

#include <iostream>
#include <Windows.h>

/**
 * Function pointer declarations.
 */
typedef void (*TestFunc1)();
typedef int (*TestFunc2)(int param);

int main()
{
    std::cout << "Hello World!\n";
	HINSTANCE hndDll = LoadLibrary(L"DllTest.dll");
	if (hndDll)
	{
		TestFunc1 TheTestFunction1 = (TestFunc1)GetProcAddress(hndDll, "TestFunction1");
		if (TheTestFunction1)
		{
			TheTestFunction1();
		}
		else
		{
			std::cout << "Could not get the address for TestFunction1, error code " << GetLastError() << std::endl;
		}

		TestFunc2 TheTestFunction2 = (TestFunc2)GetProcAddress(hndDll, "TestFunction2");
		if (TheTestFunction2)
		{
			std::cout << "Calling test function 2 with param 34 = " << TheTestFunction2(34) << std::endl;
		}
		else
		{
			std::cout << "Could not get the address for TestFunction2, error code " << GetLastError() << std::endl;
		}

		FreeLibrary(hndDll);
	}
	else
	{
		std::cout << "LoadLibrary failed, error code " << GetLastError() << std::endl;
	}
}
