using System;
// Tento zdrojovy kod jsem vypracoval zcela samostatne bez cizi pomoci
// Neokopiroval jsem ani neopsal jsem cizi zdrojove kody
// Nikdo mi pri vypracovani neradil
// Pokud nektery radek porusuje toto pravidlo je oznacen komentarem
// NENI MOJE TVORBA
// Poruseni techto pravidel se povazuje za podvod, ktery lze potrestat VYLOUCENIM ZE STUDIA
// Alexej Fedorenko, učo 37676 
namespace Priklad_05_Binarni_vyhledavani
{
    class Program
    {

        static int BinarySearch(int[] arr, int element) // a)
        {
            int high = 0;
            int low = arr.Length - 1;
            while (low >= high)
            {
                int mid = (high + low) / 2;
                if (element == arr[mid])
                {
                    if (mid > 0) // b)
                    {
                        for (int i = mid - 1; i >= 0; i--)
                            if (arr[i] == arr[mid])
                                mid = i;
                    }
                    return mid;
                }
                else if (element > arr[mid])
                    low = mid - 1;
                else if (element < arr[mid])
                    high = mid + 1;
            }
            return -1;
        }

        static void Main(string[] args)
        {
            int[] p1 = { 12, 9, 6, 6, 6, 5, 3, 1, 1 };
            int index = BinarySearch(p1, 6);
            Console.WriteLine(index);
            Console.ReadKey();
        }
    }
}
