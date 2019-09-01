using System.Runtime.InteropServices;

namespace WindowsFormsApp1
{
    /**
     * Provides the functional interface to DllTest.dll. It seems that this
     * DLL is dynamically loaded when the functions are called.
     */
    public static class DllLink
    {
        [DllImport("DllTest.dll", EntryPoint = "TestFunction1")]
        public static extern void TestFunction1();

        [DllImport("DllTest.dll", EntryPoint = "TestFunction2")]
        public static extern int TestFunction2(int param);
    }
}
