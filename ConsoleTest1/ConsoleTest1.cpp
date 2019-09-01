/**
 * ConsoleTest1
 * ------------
 * An example of how an external DLL can be referenced at compile time.
 * The DllTest project has been added as an external reference within the
 * Solution Explorer. The DllTest project has also been added as a build
 * dependency for this project.
 */
#include <iostream>

/*
 * The functions imported from the DLL need to be enclosed in this block if 
 * this module is being compiled using C++.
 */
#ifdef __cplusplus
extern "C"
{
#endif
	__declspec(dllimport) void TestFunction1();
	__declspec(dllimport) int TestFunction2(int param1);
#ifdef __cplusplus
}
#endif

int main()
{
    std::cout << "ConsoleTest1" << std::endl;
	TestFunction1();
	int param = TestFunction2(25);
	std::cout << "param is " << param << std::endl;
}
