using System;
using System.Diagnostics;
// Tento zdrojovy kod jsem vypracoval zcela samostatne bez cizi pomoci
// Neokopiroval jsem ani neopsal jsem cizi zdrojove kody
// Nikdo mi pri vypracovani neradil
// Pokud nektery radek porusuje toto pravidlo je oznacen komentarem
// NENI MOJE TVORBA
// Poruseni techto pravidel se povazuje za podvod, ktery lze potrestat VYLOUCENIM ZE STUDIA
// Alexej Fedorenko, učo 37676 
namespace Priklad_06_Vylepseny_Bubble_Sort
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
        static void Swap(ref int a, ref int b)
        {
            int temp = 0;
            Assign(ref temp, a);
            Assign(ref a, b);
            Assign(ref b, temp);
        }

        static void DescBubbleSort2(int[] array)
        {
            for (int i = 0; i < array.Length; i++)
            {
                for (int x = 0; x < array.Length - 1 - i; x++)
                    if (IsSmaller(array[x], array[x + 1]))
                        Swap(ref array[x], ref array[x + 1]);
            }
        }

        static void DescBubbleSort(int[] array)
        {
            for (int i = 0; i < array.Length; i++)
            {
                for (int x = 0; x < array.Length - 1; x++)
                    if (IsSmaller(array[x], array[x + 1]))
                        Swap(ref array[x], ref array[x + 1]);
            }
        }
        static int[] GenerateArray(int size)
        {
            if (size <= 0)
                return null;

            Random rnd = new Random();
            int[] array = new int[size];

            for (int i = 0; i < array.Length; i++)
                array[i] = rnd.Next(1, size);

            return array;
        }

        static void Copy(int[] from, int[] to)
        {
            for (int i = 0; i < to.Length; i++)
                Assign(ref to[i], from[i]);
        }
        static void ResetArrayOperationsCount()
        {
            g_assignCount = 0;
            g_comparisonCount = 0;
        }

        static void Main(string[] args) //a), b)
        {
            Stopwatch time = new Stopwatch();
            long bubbleMillis = 0, bubble2Millis = 0;
            int[] array = GenerateArray(1000);
            int[] array2 = GenerateArray(10000);
            int[] array3 = GenerateArray(30000);
            int[] array_copy = new int[1000];
            int[] array_copy2 = new int[10000];
            int[] array_copy3 = new int[30000];
            Copy(array, array_copy);
            Copy(array2, array_copy2);
            Copy(array3, array_copy3);

            Console.WriteLine("Prvku 1000");

            time.Start();
            DescBubbleSort(array_copy);
            time.Stop();

            Console.WriteLine("BubbleSort - porovnani: {0}, prirazeni: {1}", g_comparisonCount, g_assignCount);
            bubbleMillis = time.ElapsedMilliseconds;
            Copy(array, array_copy);
            ResetArrayOperationsCount();

            time.Restart();
            DescBubbleSort2(array_copy);
            time.Stop();

            Console.WriteLine("BubbleSort2 - porovnani: {0}, prirazeni: {1}", g_comparisonCount, g_assignCount);
            bubble2Millis = time.ElapsedMilliseconds;
            ResetArrayOperationsCount();

            Console.WriteLine("BubbleSort - doba behu {0} ms", bubbleMillis);
            Console.WriteLine("BubbleSort2 - doba behu {0} ms", bubble2Millis);

            Console.WriteLine("\nPrvku 10000");

            time.Restart();
            DescBubbleSort(array_copy2);
            time.Stop();

            Console.WriteLine("BubbleSort - porovnani: {0}, prirazeni: {1}", g_comparisonCount, g_assignCount);
            bubbleMillis = time.ElapsedMilliseconds;
            Copy(array2, array_copy2);
            ResetArrayOperationsCount();

            time.Restart();
            DescBubbleSort2(array_copy2);
            time.Stop();

            Console.WriteLine("BubbleSort2 - porovnani: {0}, prirazeni: {1}", g_comparisonCount, g_assignCount);
            bubble2Millis = time.ElapsedMilliseconds;
            ResetArrayOperationsCount();

            Console.WriteLine("BubbleSort - doba behu {0} ms", bubbleMillis);
            Console.WriteLine("BubbleSort2 - doba behu {0} ms", bubble2Millis);

            Console.WriteLine("\nPrvku 30000");

            time.Restart();
            DescBubbleSort(array_copy3);
            time.Stop();

            Console.WriteLine("BubbleSort - porovnani: {0}, prirazeni: {1}", g_comparisonCount, g_assignCount);
            bubbleMillis = time.ElapsedMilliseconds;
            Copy(array3, array_copy3);
            ResetArrayOperationsCount();

            time.Restart();
            DescBubbleSort2(array_copy3);
            time.Stop();

            Console.WriteLine("BubbleSort2 - porovnani: {0}, prirazeni: {1}", g_comparisonCount, g_assignCount);
            bubble2Millis = time.ElapsedMilliseconds;

            Console.WriteLine("BubbleSort - doba behu {0} ms", bubbleMillis);
            Console.WriteLine("BubbleSort2 - doba behu {0} ms", bubble2Millis);

            Console.ReadKey();

        }
    }
}
