using System;
// Tento zdrojovy kod jsem vypracoval zcela samostatne bez cizi pomoci
// Neokopiroval jsem ani neopsal jsem cizi zdrojove kody
// Nikdo mi pri vypracovani neradil
// Pokud nektery radek porusuje toto pravidlo je oznacen komentarem
// NENI MOJE TVORBA
// Poruseni techto pravidel se povazuje za podvod, ktery lze potrestat VYLOUCENIM ZE STUDIA
// Alexej Fedorenko, učo 37676 
namespace Priklad_01_Test_setridinosti_pole
{
    class Program
    {
        static bool IsSortedDescending(int[] array)
        {
            for (int i = 0; i < array.Length - 1; i++)
                if (array[i] < array[i + 1])
                    return false;

            return true;
        }

        static void Main(string[] args)
        {
            int[] array = { 15, 12, 9, 9, 8, 5, 2, 2, 1 };
            bool isSortedDescending = IsSortedDescending(array);

            Console.WriteLine(isSortedDescending);
            Console.ReadKey();
        }
    }
}
