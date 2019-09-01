# DllTest Example Solution

This Visual Studio 2019 project contains some basic example code 
highlighting the structure and use of DLLs within an application. 
There are 4 projects within this solution:

- **DllTest** contains a project that produces a basic DLL with a couple
of exported functions.

- **ConsoleTest1** is a simple console application that links to the DLL
at compile time.

- **ConsoleTest2** is a simple console application that dynamically loads
the DLL at runtime.

- **WindowsFormsApp1** is a C# .NET forms application that uses the DLL.

The project is currently configured to compile the C projects targeting
the x64 platform. This was required by the C# .NET application to be able
to access the DLL functions, but this is most likely a system 
configuration limitation - I think it's possible to install a x86 (32 bit)
version of the .NET runtime and compile the .NET application against
that, and then access a 32 bit compiled version of the DLL. Maybe there's
another way to access a 32 bit DLL from a 64 bit .NET application, that's
something I have to look into.

I would encourage changing parameters, adding functions, fiddling with 
settings and so forth to get a better understanding of how DLLs are used 
(that and a healthy dose of looking up win32 and .NET documentation).

## DllTest Project

Based on the starter project created by Visual Studio. Contains the 
[DllMain](https://docs.microsoft.com/en-us/windows/win32/dlls/dllmain) 
function, with a case statement indicating the different situations that 
this function is called. The case statements currently contain lines that
print to stdout when these situations occur.

The exported functions `TestFunction1()` and `TestFunction2()` are 
enclosed in an `extern "C"` block, but this is only "active" if the file
is compiled as a C++ program (by expecting the macro definition `__cplusplus`
to be present). `TestFunction2()` takes a simple parameter and returns a 
simple value, but there must be more investigation into dealing with allocated
memory parameter and return types when working between the DLL and a .NET 
application.

## ConsoleTest1 Project

A basic console application that refers to and requires the DLL reference at
compile time. The function prototypes for `TestFunction1()` and 
`Testfunction2()` are added to the main C++ source file but probably should
ideally be declared in a header file.

The configuration for this project sets the DllTest project as a dependency,
as well as a reference. If the reference is removed the project will fail to
compile.

## ConsoleTest2 Project

A basic console application that dynamically loads the DLL at runtime. This 
project does not need to define the DllTest project as a dependency (but it's
probably good practice to) and is able to be compiled without adding the DllTest
project as a reference. The management of the DLL happens at runtime, when the
application is executed.

Things of interest:

- The DLL is loaded via the `LoadLibrary()` win32 function, and is unloaded
via the `FreeLibrary()` win32 function. The `LoadLibrary()` function returns
a `HINSTANCE` value that is used whenever working with the DLL.

- **Function pointers** are used to retrieve functions from the DLL via the 
`GetProcAddress()` win32 function. The function signature (parameters, return
value) is defined using a `typedef` statement and a function pointer variable
is assigned the value returned from the `GetProcAddress()` function call. Note
that the function signature of the function pointer should match the function 
signature of the function being retrieved by the `GetProcAddress()`. Probably
worth noting that these function references become invalid once the DLL is freed
using `FreeLibrary()`.

## WindowsFormsApp1 Project

A basic Windows Forms application written in C#. Based on boilerplate code 
created by Visual Studio.

The `DllLink.cs` file contains the references to the functions within the
DLL. I could not add the DllTest project as a reference, and modified the 
compilation output folder to match the output folder of the DLL project.

It seems with some experimentation that the DLL is accessed in a similar 
manner to how the ConsoleTest2 project access it - dynamically at runtime.
There seems to be a bit more going on when running a debug session: the output
window seems to indicate that the `DllMain()` function was accessed a number
of times for `THREAD_ATTACH` reasons, and this may be something worth 
investigating._
