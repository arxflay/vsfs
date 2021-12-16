using System;
// Tento zdrojovy kod jsem vypracoval zcela samostatne bez cizi pomoci
// Neokopiroval jsem ani neopsal jsem cizi zdrojove kody
// Nikdo mi pri vypracovani neradil
// Pokud nektery radek porusuje toto pravidlo je oznacen komentarem
// NENI MOJE TVORBA
// Poruseni techto pravidel se povazuje za podvod, ktery lze potrestat VYLOUCENIM ZE STUDIA
// Alexej Fedorenko, učo 37676 

namespace Priklad_05_Maximum_z_pole
{
    class Program
    {
        static void MaxArray(int[] array, ref int max, ref int max2, ref int max3)
        {
            long minVal = (long)int.MinValue - 1;
            long vmax = minVal, vmax2 = minVal, vmax3 = minVal;

            for (int i = 0; i < array.Length; i++) // a)
            {
                if (array[i] > vmax)
                    vmax = array[i];
            }

            for (int i = 0; i < array.Length; i++) // b)
            {
                if (array[i] > vmax2 && array[i] != vmax)
                    vmax2 = array[i];
            }

            for (int i = 0; i < array.Length; i++) // c)
            {
                if (array[i] > vmax3 && array[i] != vmax2 && array[i] != vmax )
                    vmax3 = array[i];
            }

            if (vmax != minVal)
            {
                if (vmax2 == minVal)
                {
                    max = (int)vmax;
                    max2 = max;
                    max3 = max;
                }
                else if (vmax3 == minVal)
                {
                    max = (int)vmax;
                    max2 = (int)vmax2;
                    max3 = max2;
                }
                else
                {
                    max = (int)vmax;
                    max2 = (int)vmax2;
                    max3 = (int)vmax3;
                }
            }
        }

        static void Main(string[] args)
        {
            int max = 0, max2 = 0, max3 = 0; 
            int[] array = { 2, 5, 7, 1, 4, 6, 9, 8, 2 };
            MaxArray(array, ref max, ref max2, ref max3);

            Console.WriteLine("{0} {1} {2}", max, max2, max3);
            Console.ReadKey();

        }
    }
}
