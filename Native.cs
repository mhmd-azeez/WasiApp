using System.Runtime.CompilerServices;

namespace WasiApp
{
    internal class Native
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern static int Power(int number);

        public static int Multiply(int num1, int num2)
        {
            return num1 * num2;
        }
    }
}
