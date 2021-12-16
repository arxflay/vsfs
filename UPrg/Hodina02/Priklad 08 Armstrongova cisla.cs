using System;
// Tento zdrojovy kod jsem vypracoval zcela samostatne bez cizi pomoci
// Neokopiroval jsem ani neopsal jsem cizi zdrojove kody
// Nikdo mi pri vypracovani neradil
// Pokud nektery radek porusuje toto pravidlo je oznacen komentarem
// NENI MOJE TVORBA
// Poruseni techto pravidel se povazuje za podvod, ktery lze potrestat VYLOUCENIM ZE STUDIA
// Alexej Fedorenko, učo 37676 
namespace Priklad_08_Armstrongova_cisla
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Vsechna Armstrongova cisla mensi nez 100000: ");
            for (int i = 0; i < 100000; i++)
            {
                int numberLength = 0;
                int armstrongNumber = 0;
                int number = i;

                while (number > 0)
                {
                    number /= 10;
                    numberLength++;
                }

                number = i;

                for (int x = 0; x < numberLength; x++)
                {
                    int digit = number % 10;
                    int pow = digit;

                    for (int j = 2; j <= numberLength; j++)
                        pow *= digit;

                    number /= 10;
                    armstrongNumber += pow;
                }

                if (i == armstrongNumber)
                    Console.Write("{0}, ", i);
            }
            Console.ReadKey();
        }
    }
}
