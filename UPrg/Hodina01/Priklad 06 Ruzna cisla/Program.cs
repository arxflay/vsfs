using System;
// Tento zdrojovy kod jsem vypracoval zcela samostatne bez cizi pomoci
// Neokopiroval jsem ani neopsal jsem cizi zdrojove kody
// Nikdo mi pri vypracovani neradil
// Pokud nektery radek porusuje toto pravidlo je oznacen komentarem
// NENI MOJE TVORBA
// Poruseni techto pravidel se povazuje za podvod, ktery lze potrestat VYLOUCENIM ZE STUDIA
// Alexej Fedorenko, učo 37676

namespace Priklad_06_Ruzna_cisla
{
    class Program
    {
        static void Main(string[] args)
        {
            int a = 1, b = 2, c = 3;
            bool containsDuplicate = false;

            if (a == b)
                containsDuplicate = true;
            if (b == c)
                containsDuplicate = true;
            if (c == a)
                containsDuplicate = true;

            if (containsDuplicate)
                Console.WriteLine("{0}, {1} a {2} nejsou navzajem ruzne", a, b, c);
            else
                Console.WriteLine("{0}, {1} a {2} jsou navzajem ruzne", a, b, c);

            Console.ReadKey();
        }
    }
}
