using System;
// Tento zdrojovy kod jsem vypracoval zcela samostatne bez cizi pomoci
// Neokopiroval jsem ani neopsal jsem cizi zdrojove kody
// Nikdo mi pri vypracovani neradil
// Pokud nektery radek porusuje toto pravidlo je oznacen komentarem
// NENI MOJE TVORBA
// Poruseni techto pravidel se povazuje za podvod, ktery lze potrestat VYLOUCENIM ZE STUDIA
// Alexej Fedorenko, učo 37676 
namespace Priklad_04_Nejvetsi_ze_tri_cisel
{
    class Program
    {
        static void Main(string[] args)
        {
            int a = 1, b = 3, c = 2;
            int biggestNumber = a;

            if (b > biggestNumber)
                biggestNumber = b;
            if (c > biggestNumber)
                biggestNumber = c;

            Console.WriteLine("nejvetsi ze tri cisel: {0}", biggestNumber);
            Console.ReadKey();
        }
    }
}
