using System;
// Tento zdrojovy kod jsem vypracoval zcela samostatne bez cizi pomoci
// Neokopiroval jsem ani neopsal jsem cizi zdrojove kody
// Nikdo mi pri vypracovani neradil
// Pokud nektery radek porusuje toto pravidlo je oznacen komentarem
// NENI MOJE TVORBA
// Poruseni techto pravidel se povazuje za podvod, ktery lze potrestat VYLOUCENIM ZE STUDIA
// Alexej Fedorenko, učo 37676 
namespace Priklad_05_Nejmensi_spolecny_nasobek
{
    class Program
    {
        static void Main(string[] args)
        {
            int a = 0, b = 0;
            int divident = 1, divisor = 1;
            int temp = 0;

            Console.WriteLine("Spocteme nejmensi spolecny nasobek cisel");

            Console.Write("Zadej prvni cislo: ");
            a = Convert.ToInt32(Console.ReadLine());

            Console.Write("Zadej druhe cislo: ");
            b = Convert.ToInt32(Console.ReadLine());

            if (a > b)
            {
                divident = a;
                divisor = b;
            }
            else
            {
                divident = b;
                divisor = a;
            }

            if (divident > 0)
            {
                while (divisor > 0)
                {
                    temp = divisor;
                    divisor = divident % divisor;
                    divident = temp;
                }
            }

            Console.WriteLine("Nejmensi spolecny nasobek je {0}", (a * b) / divident);
            Console.ReadKey();

        }
    }
}
