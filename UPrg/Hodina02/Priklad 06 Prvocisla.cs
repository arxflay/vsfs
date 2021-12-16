using System;
// Tento zdrojovy kod jsem vypracoval zcela samostatne bez cizi pomoci
// Neokopiroval jsem ani neopsal jsem cizi zdrojove kody
// Nikdo mi pri vypracovani neradil
// Pokud nektery radek porusuje toto pravidlo je oznacen komentarem
// NENI MOJE TVORBA
// Poruseni techto pravidel se povazuje za podvod, ktery lze potrestat VYLOUCENIM ZE STUDIA
// Alexej Fedorenko, učo 37676 
namespace Priklad_06_Prvocisla
{
    class Program
    {
        static void Main(string[] args)
        {
            bool isPrime = true;
            int startFrom = 2;

            Console.Write("Vsechna prvocisla mensi nez 1000: ");
            for (int i = startFrom; i < 1000; i++)
            {
                if (i % 2 == 0 && i != 2) 
                    continue;

                for (int x = 2; x < i; x++)
                {
                    if (i % x == 0)
                        isPrime = false;
                }

                if (isPrime)
                {
                    if (i == startFrom)
                        Console.Write(i);
                    else
                        Console.Write(", {0}", i);
                }
                else if (!isPrime)
                    isPrime = true;           
            }
            Console.ReadKey();
        }
    }
}
