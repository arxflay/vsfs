using System;
// Tento zdrojovy kod jsem vypracoval zcela samostatne bez cizi pomoci
// Neokopiroval jsem ani neopsal jsem cizi zdrojove kody
// Nikdo mi pri vypracovani neradil
// Pokud nektery radek porusuje toto pravidlo je oznacen komentarem
// NENI MOJE TVORBA
// Poruseni techto pravidel se povazuje za podvod, ktery lze potrestat VYLOUCENIM ZE STUDIA
// Alexej Fedorenko, učo 37676 
namespace Priklad_02_Priprava_na_trideni
{
    class Program
    {
        static int g_assignCount = 0;
        static int g_comparisonCount = 0;

        static void Assign(ref int x, int val) // a)
        {
            ++g_assignCount;
            x = val;
        }

        static bool IsSmaller(int x, int y) // b)
        {
            ++g_comparisonCount;
            return x < y;
        }

        static bool IsBigger(int x, int y) // c)
        {
            ++g_comparisonCount;
            return x > y;
        }

        static void Main(string[] args)
        {
            int x = 5, y = 4, z = 3;

            bool is1 = IsSmaller(y, z);
            bool is2 = IsSmaller(x, z);
            bool is3 = IsBigger(x, y);
            Assign(ref x, y);
            Assign(ref y, z);

            Console.WriteLine("{0} {1} {2} 4={3} 3={4}", is1, is2, is3, x, y);
            Console.WriteLine("Prirazeni: {0}, Porovnani: {1}", g_assignCount, g_comparisonCount);
            Console.ReadKey();
        }
    }
}
