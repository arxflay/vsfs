using System;
// Tento zdrojovy kod jsem vypracoval zcela samostatne bez cizi pomoci
// Neokopiroval jsem ani neopsal jsem cizi zdrojove kody
// Nikdo mi pri vypracovani neradil
// Pokud nektery radek porusuje toto pravidlo je oznacen komentarem
// NENI MOJE TVORBA
// Poruseni techto pravidel se povazuje za podvod, ktery lze potrestat VYLOUCENIM ZE STUDIA
// Alexej Fedorenko, učo 37676 
namespace Priklad_03_Pocet_cisel_mensich_nez_10
{
    class Program
    {
        static void Main(string[] args)
        {
            int a = 1, b = 2, c = 3;
            int countLessThanTen = 0;

            if (a < 10)
                ++countLessThanTen;
            if (b < 10)
                ++countLessThanTen;
            if (c < 10)
                ++countLessThanTen;

            Console.WriteLine("pocet cisel mensich nez 10: {0}", countLessThanTen);
            Console.ReadKey();
        }
    }
}
