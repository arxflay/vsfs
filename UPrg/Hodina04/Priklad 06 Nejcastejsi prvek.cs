using System;
// Tento zdrojovy kod jsem vypracoval zcela samostatne bez cizi pomoci
// Neokopiroval jsem ani neopsal jsem cizi zdrojove kody
// Nikdo mi pri vypracovani neradil
// Pokud nektery radek porusuje toto pravidlo je oznacen komentarem
// NENI MOJE TVORBA
// Poruseni techto pravidel se povazuje za podvod, ktery lze potrestat VYLOUCENIM ZE STUDIA
// Alexej Fedorenko, učo 37676 

namespace Priklad_06_Nejcastejsi_prvek
{
    class Program
    {
        static int MostCommonElement(int[] array)
        {
            int mostCommonElement = 0, repeatCount = 0;

            for (int i = 0; i < array.Length; i++)
            {
                int tempMostCommonElement = array[i], tempRepeatCount = 0;

                if (mostCommonElement == array[i] && i != 0) 
                    continue;

                for (int x = i; x < array.Length; x++)
                {
                    if (array[i] == array[x])
                        tempRepeatCount++;
                }

                if (tempRepeatCount > repeatCount)
                {
                    mostCommonElement = tempMostCommonElement;
                    repeatCount = tempRepeatCount;
                }
            }

            for (int i = 0; i < array.Length; i++)
            {
                int tempRepeatCount = 1;

                if (mostCommonElement == array[i])
                    continue;

                for (int x = i; x < array.Length; x++)
                {
                    if (array[i] == array[x])
                        tempRepeatCount++;
                }

                if (tempRepeatCount == repeatCount)
                    break;
            }

            return mostCommonElement;
        }
        static void Main(string[] args)
        {
            int[] pole = { 2, 7, 6, 6, 6, 1, 7, 7, 2 };
            int modus = MostCommonElement(pole);
            Console.WriteLine(modus);
            Console.ReadKey();
        }
    }
}
