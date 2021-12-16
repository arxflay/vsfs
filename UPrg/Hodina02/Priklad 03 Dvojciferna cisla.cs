using System;
// Tento zdrojovy kod jsem vypracoval zcela samostatne bez cizi pomoci
// Neokopiroval jsem ani neopsal jsem cizi zdrojove kody
// Nikdo mi pri vypracovani neradil
// Pokud nektery radek porusuje toto pravidlo je oznacen komentarem
// NENI MOJE TVORBA
// Poruseni techto pravidel se povazuje za podvod, ktery lze potrestat VYLOUCENIM ZE STUDIA
// Alexej Fedorenko, učo 37676 
namespace Priklad_03_Dvojciferna_cisla
{
    class Program
    {
        static void Main(string[] args)
        {
            for (int i = 10; i < 100; i++)
            {
                if (i == 99)
                    Console.WriteLine("{0}"  , i);
                else
                    Console.Write("{0}, ", i);
            }
            Console.ReadKey();
        }
    }
}
