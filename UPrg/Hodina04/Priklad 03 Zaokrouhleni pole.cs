using System;
// Tento zdrojovy kod jsem vypracoval zcela samostatne bez cizi pomoci
// Neokopiroval jsem ani neopsal jsem cizi zdrojove kody
// Nikdo mi pri vypracovani neradil
// Pokud nektery radek porusuje toto pravidlo je oznacen komentarem
// NENI MOJE TVORBA
// Poruseni techto pravidel se povazuje za podvod, ktery lze potrestat VYLOUCENIM ZE STUDIA
// Alexej Fedorenko, učo 37676 

namespace Priklad_03_Zaokrouhleni_pole
{
    class Program
    {
        static double[] RoundArray(double[] array)
        {
            double[] newArray = new double[array.Length];

            for (int i = 0; i < array.Length; i++)
                newArray[i] = Math.Round(array[i]);

            return newArray;
        }

        static void Main(string[] args)
        {
            double[] array = { 5.12, -3.5996, 156, 7.9 };
            double[] roundedArray = RoundArray(array);

            for (int i = 0; i < roundedArray.Length; i++)
                Console.Write("{0} ", roundedArray[i]);

            Console.WriteLine();
            Console.ReadKey();
        }
    }
}
