using System;
// Tento zdrojovy kod jsem vypracoval zcela samostatne bez cizi pomoci
// Neokopiroval jsem ani neopsal jsem cizi zdrojove kody
// Nikdo mi pri vypracovani neradil
// Pokud nektery radek porusuje toto pravidlo je oznacen komentarem
// NENI MOJE TVORBA
// Poruseni techto pravidel se povazuje za podvod, ktery lze potrestat VYLOUCENIM ZE STUDIA
// Alexej Fedorenko, učo 37676 
namespace Priklad_07_Dokonala_cisla
{
    class Program
    {
        static void Main(string[] args)
        {
            int sum = 1;
            int startFrom = 6;

            Console.Write("Vsechna dokonala cisla mensi nez 10000: ");
            for (int i = startFrom; i < 10000; i++)
            {
                for (int x = 2; x < i; x++)
                {
                    if (i % x == 0)
                        sum += x;
                }

                if (sum == i)
                {
                    if (i == startFrom)
                        Console.Write(i);
                    else
                        Console.Write(", {0}", i);
                }
                sum = 1;
            }
            Console.ReadKey();
        }
    }
}
