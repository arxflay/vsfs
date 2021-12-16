using System;
// Tento zdrojovy kod jsem vypracoval zcela samostatne bez cizi pomoci
// Neokopiroval jsem ani neopsal jsem cizi zdrojove kody
// Nikdo mi pri vypracovani neradil
// Pokud nektery radek porusuje toto pravidlo je oznacen komentarem
// NENI MOJE TVORBA
// Poruseni techto pravidel se povazuje za podvod, ktery lze potrestat VYLOUCENIM ZE STUDIA
// Alexej Fedorenko, učo 37676 

namespace Priklad_02_Absolutni_hodnota_pole
{
    class Program
    {
        static int Abs(int num)
        {
            if (num < 0)
                num *= -1;

            return num;
        }

        static void AbsArray(int[] array)
        {
            for (int i = 0; i < array.Length; i++)
            {
                if (array[i] <= 0)
                    array[i] = Abs(array[i]);
            }
        }

        static void Main(string[] args)
        {
            int[] array = { 5, -2, 0, -1, 7, -12, 2, 4 };
            AbsArray(array);

            for (int i = 0; i < array.Length; i++)
                Console.Write("{0} ", array[i]);

            Console.WriteLine();
            Console.ReadKey();
        }
    }
}
