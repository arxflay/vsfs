using System;
// Tento zdrojovy kod jsem vypracoval zcela samostatne bez cizi pomoci
// Neokopiroval jsem ani neopsal jsem cizi zdrojove kody
// Nikdo mi pri vypracovani neradil
// Pokud nektery radek porusuje toto pravidlo je oznacen komentarem
// NENI MOJE TVORBA
// Poruseni techto pravidel se povazuje za podvod, ktery lze potrestat VYLOUCENIM ZE STUDIA
// Alexej Fedorenko, učo 37676 
namespace Priklad_05_Prostredni_ze_tri_cisel
{
    class Program
    {
        static void Main(string[] args)
        {
            int a = 20, b = 30, c = 10;
            int biggestNumber = a;
            int lowestNumber = a;

            if (b > biggestNumber)
                biggestNumber = b;
            if (c > biggestNumber)
                biggestNumber = c;

            if (lowestNumber > b)
                lowestNumber = b;
            if (lowestNumber > c)
                lowestNumber = c;

            int secondBiggestNumber = lowestNumber;

            if (a != biggestNumber)
                if (a > secondBiggestNumber) secondBiggestNumber = a;
            if (b != biggestNumber)
                if (b > secondBiggestNumber) secondBiggestNumber = b;
            if (c != biggestNumber)
                if (c > secondBiggestNumber) secondBiggestNumber = c;

            Console.WriteLine("Prostredni z hodnot {0} {1} {2} je {3}", a, b, c, secondBiggestNumber);
            Console.ReadKey();

        }
    }
}
