using System;
// Tento zdrojovy kod jsem vypracoval zcela samostatne bez cizi pomoci
// Neokopiroval jsem ani neopsal jsem cizi zdrojove kody
// Nikdo mi pri vypracovani neradil
// Pokud nektery radek porusuje toto pravidlo je oznacen komentarem
// NENI MOJE TVORBA
// Poruseni techto pravidel se povazuje za podvod, ktery lze potrestat VYLOUCENIM ZE STUDIA
// Alexej Fedorenko, učo 37676 
namespace Priklad_07_Vylepseny_Count_Sort
{
    class Program
    {
        static void DescCountingSort(int[] array)
        {
            int max = int.MinValue;
            int min = 0;
            int[] count;
            int[] aux = new int[array.Length];
            int prev = 0;
            int sum = 0;

            for (int i = 0; i < array.Length; i++)
                if (array[i] > max) max = array[i];

            for (int i = 0; i < array.Length; i++)
                if (array[i] < min) min = array[i];

            int minAbs = Math.Abs(min);
            count = new int[minAbs + max + 1];

            for (int i = 0; i < array.Length; i++)
                count[array[i] + minAbs]++;

            for (int i = count.Length - 1; i >= 0; i--)
            {
                prev = sum;
                sum += count[i];
                count[i] = prev;
            }

            for (int i = 0; i < array.Length; i++)
            {
                aux[count[array[i] + minAbs]] = array[i];
                count[array[i] + minAbs]++;
            }

            for (int i = 0; i < array.Length; i++)
                array[i] = aux[i];
        }

        static void Main(string[] args)
        {
            int[] p1 = { -5, 7, 15, 22, 4, 0, 4, 9, -11 };
            DescCountingSort(p1);

            for (int i = 0; i < p1.Length; i++)
                Console.Write("{0}, ", p1[i]);

            Console.ReadKey();
        }
    }
}
