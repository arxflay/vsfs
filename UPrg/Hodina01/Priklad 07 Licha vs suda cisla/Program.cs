using System;
// Tento zdrojovy kod jsem vypracoval zcela samostatne bez cizi pomoci
// Neokopiroval jsem ani neopsal jsem cizi zdrojove kody
// Nikdo mi pri vypracovani neradil
// Pokud nektery radek porusuje toto pravidlo je oznacen komentarem
// NENI MOJE TVORBA
// Poruseni techto pravidel se povazuje za podvod, ktery lze potrestat VYLOUCENIM ZE STUDIA
// Alexej Fedorenko, učo 37676 
namespace Priklad_07_Licha_vs_suda_cisla
{
    class Program
    {
        static void Main(string[] args)
        {
            int a = 1, b = 2, c = 3;
            int evenSum = 0, oddSum = 0;

            if (a % 2 == 0)
                evenSum += a;
            else
                oddSum += a;

            if (b % 2 == 0)
                evenSum += b;
            else
                oddSum += b;

            if (c % 2 == 0)
                evenSum += c;
            else
                oddSum += c;

            if (oddSum > evenSum)
                Console.WriteLine("Zadana cisla {0}, {1}, {2} maji soucet lichych hodnot {3} vyssi nez soucet sudych hodnot {4} "
                    , a, b, c, oddSum, evenSum);

            Console.ReadKey();
        }
    }
}
