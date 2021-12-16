using System;
// Tento zdrojovy kod jsem vypracoval zcela samostatne bez cizi pomoci
// Neokopiroval jsem ani neopsal jsem cizi zdrojove kody
// Nikdo mi pri vypracovani neradil
// Pokud nektery radek porusuje toto pravidlo je oznacen komentarem
// NENI MOJE TVORBA
// Poruseni techto pravidel se povazuje za podvod, ktery lze potrestat VYLOUCENIM ZE STUDIA
// Alexej Fedorenko, učo 37676 
namespace Priklad_08_Delitel_cisla
{
    class Program
    {
        static void Main(string[] args)
        {
            int a = 1, b = 2, c = 4;
            int num = 0, del = 0;

            if (a % b == 0)
            {
                num = a;
                del = b;
            }
            if (a % c == 0)
            {
                num = a;
                del = c;
            }
            if (b % a == 0)
            {
                num = b;
                del = a;
            }
            if (b % c == 0)
            {
                num = b;
                del = c;
            }
            if (c % a == 0)
            {
                num = c;
                del = a;
            }
            if (c % b == 0)
            {
                num = c;
                del = b;
            }

            if (del != 0)
                Console.WriteLine("Ze zadanych cisel {0}, {1}, {2} je cislo {3} delitelem {4}", a, b, c, del, num);
            else
                Console.WriteLine("Ze zadanych cisel {0}, {1}, {2} neni zadno cislo delitelem jineho cisla", a, b, c);

            Console.ReadKey();
        }
    }
}
