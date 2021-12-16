using System;
// Tento zdrojovy kod jsem vypracoval zcela samostatne bez cizi pomoci
// Neokopiroval jsem ani neopsal jsem cizi zdrojove kody
// Nikdo mi pri vypracovani neradil
// Pokud nektery radek porusuje toto pravidlo je oznacen komentarem
// NENI MOJE TVORBA
// Poruseni techto pravidel se povazuje za podvod, ktery lze potrestat VYLOUCENIM ZE STUDIA
// Alexej Fedorenko, učo 37676 
namespace Priklad_01_Dve_cisla_sestupne
{
    class Program
    {
        static void Main(string[] args)
        {
            int a = 0, b = 0;
            int temp = 0;
            Console.WriteLine("Setridime dve cisla sestupne");

            Console.Write("Zadejte prvni cislo: ");
            a = Convert.ToInt32(Console.ReadLine());

            Console.Write("Zadejte druhe cislo: ");
            b = Convert.ToInt32(Console.ReadLine());

            if (b > a)
            {
                temp = a;
                a = b;
                b = temp;
            }

            Console.WriteLine("Setridena cisla jsou {0} {1}", a, b);
            Console.ReadKey();

            
        }
    }
}
