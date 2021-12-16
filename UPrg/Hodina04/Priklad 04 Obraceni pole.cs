using System;
// Tento zdrojovy kod jsem vypracoval zcela samostatne bez cizi pomoci
// Neokopiroval jsem ani neopsal jsem cizi zdrojove kody
// Nikdo mi pri vypracovani neradil
// Pokud nektery radek porusuje toto pravidlo je oznacen komentarem
// NENI MOJE TVORBA
// Poruseni techto pravidel se povazuje za podvod, ktery lze potrestat VYLOUCENIM ZE STUDIA
// Alexej Fedorenko, učo 37676 

namespace Priklad_04_Obraceni_pole
{
    class Program
    {
        static void ReverseArray(int[] array)
        {
            int mid = array.Length / 2;
            for (int i = 0; i < mid; i++)
            {
                int temp = array[i];
                array[i] = array[array.Length - 1 - i];
                array[array.Length - 1 - i] = temp;
            }
        }
        static void Main(string[] args)
        {
            int[] array = { 5, 7, 2, 1, 0, 6 };
            ReverseArray(array);

            for (int i = 0; i < array.Length; i++)
                Console.Write("{0} ", array[i]);

            Console.WriteLine();
            Console.ReadKey();

        }
    }
}
