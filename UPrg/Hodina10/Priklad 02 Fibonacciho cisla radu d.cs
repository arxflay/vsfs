// Tento zdrojovy kod jsem vypracoval zcela samostatne bez cizi pomoci
// Neokopiroval jsem ani neopsal jsem cizi zdrojove kody
// Nikdo mi pri vypracovani neradil
// Pokud nektery radek porusuje toto pravidlo je oznacen komentarem
// NENI MOJE TVORBA
// Poruseni techto pravidel se povazuje za podvod, ktery lze potrestat VYLOUCENIM ZE STUDIA
// Alexej Fedorenko, učo 37676 
using System;

namespace Priklad_02_Fibonacciho_cisla_radu_d
{
    class Program
    {
        private static int FibonacciRec(int d, int n) //a)
        {
            if (d <= 1 || n < d)
                return 0;
            else if (n == d)
                return 1;

            int result = 0;
            int end = d;

            if (n - d < d) // optimized to avoid recursion n < d
                end = n - end;

            for (int i = 1; i <= end; i++)
                result += FibonacciRec(d, n - i);

            return result;
        }

        private static int Fibonacci(int d, int n) //b)
        {
            if (d <= 1 || n < d)
                return 0;
            else if (n == d)
                return 1;

            int count = n - d + 1;
            
            int[] sequence = new int[count];
            sequence[0] = 1;

            for(int i = 1; i < count; i++)
            {
                int sum = 0;

                for (int x = 1; x <= d && i - x >= 0; x++)
                    sum += sequence[i - x];

                sequence[i] = sum;
            }

            return sequence[count - 1];
        }

        private static void Main(string[] args)
        {
            Console.WriteLine("FRec(3, 8) {0}", FibonacciRec(3, 8));
            Console.WriteLine("FRec(4, 16) {0}", FibonacciRec(4, 16));
            Console.WriteLine("FRec(5, 13) {0}", FibonacciRec(5, 13));
            Console.WriteLine("FRec(200, 212) {0}", FibonacciRec(200, 212));
            
            Console.WriteLine("Fib(3, 8) {0}", Fibonacci(3,8));
            Console.WriteLine("Fib(4, 16) {0}",Fibonacci(4,16));
            Console.WriteLine("Fib(5, 13) {0}",Fibonacci(5,13));
            Console.WriteLine("Fib(200, 212) {0}",Fibonacci(200,212));
        }
    }
}
