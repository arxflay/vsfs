using System;
using System.Diagnostics;
// Tento zdrojovy kod jsem vypracoval zcela samostatne bez cizi pomoci
// Neokopiroval jsem ani neopsal jsem cizi zdrojove kody
// Nikdo mi pri vypracovani neradil
// Pokud nektery radek porusuje toto pravidlo je oznacen komentarem
// NENI MOJE TVORBA
// Poruseni techto pravidel se povazuje za podvod, ktery lze potrestat VYLOUCENIM ZE STUDIA
// Alexej Fedorenko, učo 37676 
namespace Priklad_04_Testovani_rychlosti_algoritmu
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

        static void ResetArrayOperationsCount()
        {
            g_assignCount = 0;
            g_comparisonCount = 0;
        }

        static bool IsSortedDescending(int[] array)
        {
            for (int i = 0; i < array.Length - 1; i++)
            {
                if (array[i] < array[i + 1])
                    return false;
            }
            return true;
        }

        static void DescBubbleSort(int[] array)
        {
            for (int i = 0; i < array.Length; i++)
            {
                for (int x = 0; x < array.Length - 1 - i; x++)
                    if (IsSmaller(array[x], array[x + 1]))
                        Swap(ref array[x], ref array[x + 1]);
            }
        }

        static void DescSelectionSort(int[] array)
        {
            int biggestIndex = 0;
            for (int i = 0; i < array.Length - 1; i++)
            {
                biggestIndex = i;
                for (int x = i; x < array.Length; x++)
                    if (IsBigger(array[x], array[biggestIndex]))
                        biggestIndex = x;

                Swap(ref array[biggestIndex], ref array[i]);
            }
        }

        static void DescInsertionSort(int[] array)
        {
            for (int i = 0; i < array.Length; i++)
            {
                for (int j = i; j > 0 && IsBigger(array[j], array[j - 1]); j--)
                    Swap(ref array[j], ref array[j - 1]);
            }
        }

        static void DescCountingSort(int[] array)
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

        static int[] GenerateArray(int size)
        {
            if (size <= 0)
                return null;

            Random rnd = new Random();
            int[] array = new int[size];

            for (int i =0; i < array.Length; i++)
                array[i] = rnd.Next(1, size);

            return array;
        }

        static void Copy(int[] from, int[] to)
        {
            for (int i = 0; i < to.Length; i++)
                Assign(ref to[i], from[i]);
        }

        static void Main(string[] args) //a), b)
        {
            long bubbleMillis = 0, selectionMillis = 0, insertionMillis = 0, countMillis = 0;
            int[] array = GenerateArray(1000);
            int[] array2 = GenerateArray(10000);
            int[] array3 = GenerateArray(30000);
            int[] array_copy = new int[1000];
            int[] array_copy2 = new int[10000];
            int[] array_copy3 = new int[30000];
            Copy(array, array_copy);
            Copy(array2, array_copy2);
            Copy(array3, array_copy3);

            Stopwatch time = new Stopwatch();

            Console.WriteLine("Prvku 1000");

            time.Start();
            DescBubbleSort(array_copy);
            time.Stop();

            Console.WriteLine("BubbleSort - porovnani: {0}, prirazeni: {1}", g_comparisonCount, g_assignCount);
            bubbleMillis = time.ElapsedMilliseconds;
            Copy(array, array_copy);
            ResetArrayOperationsCount();

            time.Restart();
            DescSelectionSort(array_copy);
            time.Stop();

            Console.WriteLine("SelectionSort - porovnani: {0}, prirazeni: {1}", g_comparisonCount, g_assignCount);
            selectionMillis = time.ElapsedMilliseconds;
            Copy(array, array_copy);
            ResetArrayOperationsCount();

            time.Restart();
            DescInsertionSort(array_copy);
            time.Stop();

            Console.WriteLine("InsertionSort - porovnani: {0}, prirazeni: {1}", g_comparisonCount, g_assignCount);
            insertionMillis = time.ElapsedMilliseconds;
            Copy(array, array_copy);
            ResetArrayOperationsCount();

            time.Restart();
            DescCountingSort(array_copy);
            time.Stop();

            Console.WriteLine("CountSort - porovnani: {0}, prirazeni: {1}", g_comparisonCount, g_assignCount);
            countMillis = time.ElapsedMilliseconds;
            ResetArrayOperationsCount();

            Console.WriteLine("\nBubbleSort - doba behu {0} ms", bubbleMillis);
            Console.WriteLine("SelectionSort - doba behu {0} ms", selectionMillis);
            Console.WriteLine("InsertionSort - doba behu {0} ms", insertionMillis);
            Console.WriteLine("InsertionSort - doba behu {0} ms", countMillis);

            Console.WriteLine("\nPrvku 10000");

            time.Restart();
            DescBubbleSort(array_copy2);
            time.Stop();

            Console.WriteLine("BubbleSort - porovnani: {0}, prirazeni: {1}", g_comparisonCount, g_assignCount);
            bubbleMillis = time.ElapsedMilliseconds;
            Copy(array2, array_copy2);
            ResetArrayOperationsCount();

            time.Restart();
            DescSelectionSort(array_copy2);
            time.Stop();

            Console.WriteLine("SelectionSort - porovnani: {0}, prirazeni: {1}", g_comparisonCount, g_assignCount);
            selectionMillis = time.ElapsedMilliseconds;
            Copy(array2, array_copy2);
            ResetArrayOperationsCount();

            time.Restart();
            DescInsertionSort(array_copy2);
            time.Stop();

            Console.WriteLine("InsertionSort - porovnani: {0}, prirazeni: {1}", g_comparisonCount, g_assignCount);
            insertionMillis = time.ElapsedMilliseconds;
            Copy(array2, array_copy2);
            ResetArrayOperationsCount();

            time.Restart();
            DescCountingSort(array_copy2);
            time.Stop();

            Console.WriteLine("CountSort - porovnani: {0}, prirazeni: {1}", g_comparisonCount, g_assignCount);
            countMillis = time.ElapsedMilliseconds;
            ResetArrayOperationsCount();

            Console.WriteLine("\nBubbleSort - doba behu {0} ms", bubbleMillis);
            Console.WriteLine("SelectionSort - doba behu {0} ms", selectionMillis);
            Console.WriteLine("InsertionSort - doba behu {0} ms", insertionMillis);
            Console.WriteLine("InsertionSort - doba behu {0} ms", countMillis);

            Console.WriteLine("\nPrvku 30000");

            time.Restart();
            DescBubbleSort(array_copy3);
            time.Stop();

            Console.WriteLine("BubbleSort - porovnani: {0}, prirazeni: {1}", g_comparisonCount, g_assignCount);
            bubbleMillis = time.ElapsedMilliseconds;
            Copy(array3, array_copy3);
            ResetArrayOperationsCount();

            time.Restart();
            DescSelectionSort(array_copy3);
            time.Stop();

            Console.WriteLine("SelectionSort - porovnani: {0}, prirazeni: {1}", g_comparisonCount, g_assignCount);
            selectionMillis = time.ElapsedMilliseconds;
            Copy(array3, array_copy3);
            ResetArrayOperationsCount();

            time.Restart();
            DescInsertionSort(array_copy3);
            time.Stop();

            Console.WriteLine("InsertionSort - porovnani: {0}, prirazeni: {1}", g_comparisonCount, g_assignCount);
            insertionMillis = time.ElapsedMilliseconds;
            Copy(array3, array_copy3);
            ResetArrayOperationsCount();

            time.Restart();
            DescCountingSort(array_copy3);
            time.Stop();

            Console.WriteLine("CountSort - porovnani: {0}, prirazeni: {1}", g_comparisonCount, g_assignCount);
            countMillis = time.ElapsedMilliseconds;

            Console.WriteLine("\nBubbleSort - doba behu {0} ms", bubbleMillis);
            Console.WriteLine("SelectionSort - doba behu {0} ms", selectionMillis);
            Console.WriteLine("InsertionSort - doba behu {0} ms", insertionMillis);
            Console.WriteLine("InsertionSort - doba behu {0} ms", countMillis);

            Console.ReadKey();

        }
    }
}
