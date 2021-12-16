using System;
// Tento zdrojovy kod jsem vypracoval zcela samostatne bez cizi pomoci
// Neokopiroval jsem ani neopsal jsem cizi zdrojove kody
// Nikdo mi pri vypracovani neradil
// Pokud nektery radek porusuje toto pravidlo je oznacen komentarem
// NENI MOJE TVORBA
// Poruseni techto pravidel se povazuje za podvod, ktery lze potrestat VYLOUCENIM ZE STUDIA
// Alexej Fedorenko, učo 37676 
namespace Priklad_09_Statisticke_informace
{
    class Program
    {
        static void Main(string[] args)
        {
            int nCount = 0;
            int nSum = 0;
            int biggestNumber = -1;
            int secondBiggestNumber = -1;
            int lowestNumber = -1;
            int secondLowestNumber = -1;
            int prevNum = -1;

            while (true)
            {
                int num = 0;
                Console.Write("Zadejte cislo: ");
                num = Convert.ToInt32(Console.ReadLine());

                if (num <= 0)
                    break;

                ++nCount; //a)

                nSum += num; //b)

                if (num > biggestNumber) //c)
                    biggestNumber = num;
                if (prevNum > secondBiggestNumber && prevNum < biggestNumber || num > secondBiggestNumber && num < biggestNumber) //e)
                    secondBiggestNumber = num;
                if (num < lowestNumber || lowestNumber == -1) //d)
                    lowestNumber = num;
                else if (num < secondLowestNumber  && num > lowestNumber || secondLowestNumber == -1) //f)
                    secondLowestNumber = num;
                prevNum = num;
            }
            Console.WriteLine("Delka posloupnosti: {0}", nCount);
            if (nCount > 1)
            {
                Console.WriteLine("Soucet hodnot posloupnosti: {0}", nSum);
                Console.WriteLine("Nejmensi prvek: {0}, Druhy nejmensi prvek: {1}", lowestNumber, secondLowestNumber);
                Console.WriteLine("Nejvetsi prvek: {0}, Druhy nejvetsi prvek: {1}", biggestNumber, secondBiggestNumber);
            }
            Console.ReadKey();
        }
    }
}
