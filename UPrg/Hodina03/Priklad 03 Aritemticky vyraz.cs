using System;
// Tento zdrojovy kod jsem vypracoval zcela samostatne bez cizi pomoci
// Neokopiroval jsem ani neopsal jsem cizi zdrojove kody
// Nikdo mi pri vypracovani neradil
// Pokud nektery radek porusuje toto pravidlo je oznacen komentarem
// NENI MOJE TVORBA
// Poruseni techto pravidel se povazuje za podvod, ktery lze potrestat VYLOUCENIM ZE STUDIA
// Alexej Fedorenko, učo 37676 
namespace Priklad_03_Aritmeticky_vyraz
{
    class Program
    {
        static double Factorial(int n)         // a)
        {
            double nFactorial = 1;

            for (int i = 1; i <= n; i++)
                nFactorial *= i;

            return nFactorial;
        }

        static double Pow(double n, uint k)    // b)
        {
            double nPow = 1;

            for (int i = 1; i <= k; i++)
                nPow *= n;

            return nPow;
        }
        
        static double EPoweredByN(double n)    // c)
        {
            double nPow = 1;
            double e = 0;

            for (int i = 0; i < 100; i++)
            {
                if (i > 0)
                    nPow *= n;
                e += nPow / Factorial(i);
            }

            return e;
        }

        static double Combination(int n, int k) // d)
        {
            if (n < 0 || k < 0 || k > n)
                return 0;

            return Factorial(n) / (Factorial(k) * Factorial(n - k));
        }

        static void Main(string[] args)
        {
            double x = 0, y = 0, z = 0, a = 0, b = 0;
            x = Factorial(11);
            y = Pow(5, 3);
            z = Pow(2.69, 7);
            a = EPoweredByN(5.14);
            b = Combination(49, 6);

            Console.WriteLine("F={0} P={1}; {2} E^N={3} C(n,k)={4}", x, y, z, a, b);
            Console.ReadKey();

        }
    }
}
