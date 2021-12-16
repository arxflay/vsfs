using System;
// Tento zdrojovy kod jsem vypracoval zcela samostatne bez cizi pomoci
// Neokopiroval jsem ani neopsal jsem cizi zdrojove kody
// Nikdo mi pri vypracovani neradil
// Pokud nektery radek porusuje toto pravidlo je oznacen komentarem
// NENI MOJE TVORBA
// Poruseni techto pravidel se povazuje za podvod, ktery lze potrestat VYLOUCENIM ZE STUDIA
// Alexej Fedorenko, učo 37676 
namespace Priklad_07_Skalarni_soucin
{
    class Program
    {
        static int ScalarVector(int[] a, int[] b)
        {
            if (a.Length != b.Length)
                return -1;

            int scalar = 0;

            for (int i = 0; i < a.Length; i++)
                scalar += a[i] * b[i];

            return scalar;
        }
        static void Main(string[] args)
        {
            int[] u = { 2, 0, -5, 1, 4 };
            int[] v = { 7, 4, 2, -2, 0 };
            int scalar = ScalarVector(u, v);

            Console.WriteLine("Skalarni soucin: {0}", scalar);
            Console.ReadKey();
        }
    }
}
