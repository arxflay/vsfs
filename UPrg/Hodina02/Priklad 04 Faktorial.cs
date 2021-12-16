using System;
// Tento zdrojovy kod jsem vypracoval zcela samostatne bez cizi pomoci
// Neokopiroval jsem ani neopsal jsem cizi zdrojove kody
// Nikdo mi pri vypracovani neradil
// Pokud nektery radek porusuje toto pravidlo je oznacen komentarem
// NENI MOJE TVORBA
// Poruseni techto pravidel se povazuje za podvod, ktery lze potrestat VYLOUCENIM ZE STUDIA
// Alexej Fedorenko, učo 37676 
namespace Priklad_04_Factorial
{
    class Program
    {
        static void Main(string[] args)
        {
            int n = 0, nFactorial = 1;

            Console.WriteLine("Vypocteme faktorial kladneho cisla");
            Console.Write("Zadejte cislo: ");
            n = Convert.ToInt32(Console.ReadLine());

            if (n > 0)
            {
                for (int i = 1; i <= n; i++)
                    nFactorial *= i;
                Console.WriteLine("Factorial je {0}", nFactorial);
            }

            Console.ReadKey();
        }
    }
}
