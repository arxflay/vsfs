using System;
// Tento zdrojovy kod jsem vypracoval zcela samostatne bez cizi pomoci
// Neokopiroval jsem ani neopsal jsem cizi zdrojove kody
// Nikdo mi pri vypracovani neradil
// Pokud nektery radek porusuje toto pravidlo je oznacen komentarem
// NENI MOJE TVORBA
// Poruseni techto pravidel se povazuje za podvod, ktery lze potrestat VYLOUCENIM ZE STUDIA
// Alexej Fedorenko, učo 37676 
namespace Priklad_02_Tri_cisla_vzestupne
{
    class Program
    {
        static void Main(string[] args)
        {
            int a = 0, b = 0, c = 0;
            int temp = 0;
            Console.WriteLine("Setridime tri cisla vzestupne");

            Console.Write("Zadejte prvni cislo: ");
            a = int.Parse(Console.ReadLine());

            Console.Write("Zadejte druhe cislo: ");
            b = int.Parse(Console.ReadLine());

            Console.Write("Zadejte treti cislo: ");
            c = int.Parse(Console.ReadLine());

            if (a > c)
            {
                temp = c;
                c = a;
                a = temp;
            }

            if (b > c)
            {
                temp = c;
                c = b;
                b = temp;
            }
            else if (a > b)
            {
                temp = a;
                a = b;
                b = temp;
            }

            Console.WriteLine("Cisla jsou {0} {1} {2}", a, b, c);
            Console.ReadKey();
        }
    }
}
