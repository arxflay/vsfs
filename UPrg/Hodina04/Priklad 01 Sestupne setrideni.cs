using System;
// Tento zdrojovy kod jsem vypracoval zcela samostatne bez cizi pomoci
// Neokopiroval jsem ani neopsal jsem cizi zdrojove kody
// Nikdo mi pri vypracovani neradil
// Pokud nektery radek porusuje toto pravidlo je oznacen komentarem
// NENI MOJE TVORBA
// Poruseni techto pravidel se povazuje za podvod, ktery lze potrestat VYLOUCENIM ZE STUDIA
// Alexej Fedorenko, učo 37676 

namespace Priklad_01_Sestupne_setrideni
{
    class Program
    {
        static void SortDescending(ref int a, ref int b)
        {
            if (b > a)
            {
                int temp = a;
                a = b;
                b = temp;
            }
        }

        static void Main(string[] args)
        {
            int a = 5, b = 7;
            SortDescending(ref a, ref b);
            Console.WriteLine("a = {0}, b = {1}", a, b);
            Console.ReadKey();
        }
    }
}
