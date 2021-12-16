using System;
// Tento zdrojovy kod jsem vypracoval zcela samostatne bez cizi pomoci
// Neokopiroval jsem ani neopsal jsem cizi zdrojove kody
// Nikdo mi pri vypracovani neradil
// Pokud nektery radek porusuje toto pravidlo je oznacen komentarem
// NENI MOJE TVORBA
// Poruseni techto pravidel se povazuje za podvod, ktery lze potrestat VYLOUCENIM ZE STUDIA
// Alexej Fedorenko, učo 37676 
namespace Priklad_03_Sestupne_trideni
{
    class Program
    {
        static int g_assignCount = 0;
        static int g_comparisonCount = 0;

        static void Assign(ref int x, int val) 
        {
            ++g_assignCount;
            x = val;
        }

        static bool IsSmaller(int x, int y)
        {
            ++g_comparisonCount;
            return x < y;
        }

        static bool IsBigger(int x, int y) 
        {
            ++g_comparisonCount;
            return x > y;
        }

        static void Swap(ref int a, ref int b)
        {
            int temp = 0;
            Assign(ref temp, a);
            Assign(ref a, b);
            Assign(ref b, temp);
        }

        static bool IsSortedDescending(int[] array)
        {
            for (int i = 0; i < array.Length - 1; i++)
                if (array[i] < array[i + 1])
                    return false;

            return true;
        }

        static void DescBubbleSort(int[] array) //c)
        {
            for (int i = 0; i < array.Length; i++)
            {
                for (int x = 0; x < array.Length - 1 - i; x++)
                    if (IsSmaller(array[x], array[x + 1]))
                        Swap(ref array[x], ref array[x + 1]);
            }
        }

        static void DescSelectionSort(int[] array) //a)
        {
            for (int i = 0; i < array.Length - 1; i++)
            {
                int biggestIndex = i;
                for (int x = i; x < array.Length; x++)
                    if (IsBigger(array[x], array[biggestIndex]))
                        Assign(ref biggestIndex, x);

                Swap(ref array[biggestIndex], ref array[i]);
            }
        }

        static void DescInsertionSort(int[] array) //b)
        {
            for (int i = 0; i < array.Length; i++)
            {
                for (int j = i; j > 0 && IsBigger(array[j], array[j - 1]); j--)
                    Swap(ref array[j], ref array[j - 1]);
            }
        }

        static void DescCountingSort(int[] array) //d)
        {
            int max = int.MinValue;
            int[] count;
            int[] aux = new int[array.Length];
            int prev = 0;
            int sum = 0;
            for (int i = 0; i < array.Length; i++)
                if (IsBigger(array[i], max)) max = array[i];

            count = new int[max + 1];

            for (int i = 0; i < array.Length; i++)
                count[array[i]]++;

            for (int i = count.Length - 1; i >= 0; i--)
            {
                prev = sum;
                sum += count[i];
                count[i] = prev;
            }

            for (int i = 0; i < array.Length; i++)
            {
                Assign(ref aux[count[array[i]]], array[i]);
                count[array[i]]++;
            }

            for (int i = 0; i < array.Length; i++)
                Assign(ref array[i], aux[i]);
        }


        static void Main(string[] args)
        {
            int[] array = { 5, 7, 1, 5, 6, 8, 9, 0, 1, 2 };
            DescBubbleSort(array);
            Console.WriteLine("Prirazeni: {0}, Porovnani: {1}, Je serazen sestupne: {2}", g_assignCount, g_comparisonCount, IsSortedDescending(array));

            array = new int[] { 5, 7, 1, 5, 6, 8, 9, 0, 1, 2 };
            g_assignCount = 0;
            g_comparisonCount = 0;
            DescSelectionSort(array);

            Console.WriteLine("Prirazeni: {0}, Porovnani: {1}, Je serazen sestupne: {2}", g_assignCount, g_comparisonCount, IsSortedDescending(array));

            array = new int[] { 5, 7, 1, 5, 6, 8, 9, 0, 1, 2 };
            g_assignCount = 0;
            g_comparisonCount = 0;
            DescInsertionSort(array);

            Console.WriteLine("Prirazeni: {0}, Porovnani: {1}, Je serazen sestupne: {2}", g_assignCount, g_comparisonCount, IsSortedDescending(array));

            array = new int[] { 5, 7, 1, 5, 6, 8, 9, 0, 1, 2 };
            g_assignCount = 0;
            g_comparisonCount = 0;
            DescCountingSort(array);

            Console.WriteLine("Prirazeni: {0}, Porovnani: {1}, Je serazen sestupne: {2}", g_assignCount, g_comparisonCount, IsSortedDescending(array));

            for (int i = 0; i < array.Length; i++)
                Console.WriteLine("{0}, ", array[i]);

            Console.ReadKey();
        }
    }
}
