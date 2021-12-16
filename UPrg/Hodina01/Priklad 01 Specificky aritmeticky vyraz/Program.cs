using System;
// Tento zdrojovy kod jsem vypracoval zcela samostatne bez cizi pomoci
// Neokopiroval jsem ani neopsal jsem cizi zdrojove kody
// Nikdo mi pri vypracovani neradil
// Pokud nektery radek porusuje toto pravidlo je oznacen komentarem
// NENI MOJE TVORBA
// Poruseni techto pravidel se povazuje za podvod, ktery lze potrestat VYLOUCENIM ZE STUDIA
// Alexej Fedorenko, učo 37676 
namespace Priklad_00_Specificky_aritmeticky_vyraz
{
    class Program
    {
        static void Main(string[] args)
        {
            int a = 1, b = 2, c = 3;
            int result = b * c - a;

            Console.WriteLine("Vysledek vyrazu {0} * {1} - {2} je {3}", b, c, a, result);
            Console.ReadKey();
        }
    }
}
