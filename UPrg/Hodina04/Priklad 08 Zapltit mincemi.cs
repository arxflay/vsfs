using System;
// Tento zdrojovy kod jsem vypracoval zcela samostatne bez cizi pomoci
// Neokopiroval jsem ani neopsal jsem cizi zdrojove kody
// Nikdo mi pri vypracovani neradil
// Pokud nektery radek porusuje toto pravidlo je oznacen komentarem
// NENI MOJE TVORBA
// Poruseni techto pravidel se povazuje za podvod, ktery lze potrestat VYLOUCENIM ZE STUDIA
// Alexej Fedorenko, učo 37676 
namespace Priklad_08_Zaplatit_mincemi
{
    class Program
    {
        static int PayWithCoins(int[] coins, int price) //a)
        {
            if (price <= 0)
                return 0;

            long count = (long)int.MaxValue + 1; //pokud pocet minci bude roven int.MaxValue 
            for (int i = 0; i < coins.Length; i++)
            {
                int num = 0;
                int tempCount = 0;
                for (int j = i; j < coins.Length; j++)
                {
                    while (num <= price)
                    {
                        ++tempCount;
                        num += coins[j];
                    }
                    if (num > price)
                    {
                        --tempCount;
                        num -= coins[j];
                    }
                    if (tempCount < count && tempCount != 0 && num == price)
                    {
                        count = tempCount;
                        break;
                    }
                }
            }
            if (count == (long)int.MaxValue + 1)
                count = 0;

            return (int)count;
        }
        static void Main(string[] args)
        {
            int[] coins = { 50, 20, 10, 5, 2, 1 };

            int count = PayWithCoins(coins, 97);
            Console.WriteLine("pocet minci: {0}", count);

            count = PayWithCoins(coins, 88);
            Console.WriteLine("pocet minci: {0}", count);

            count = PayWithCoins(coins, 26);
            Console.WriteLine("pocet minci: {0}", count);

            int[] coins2 = { 50, 20, 10, 7, 5, 2, 1 };

            count = PayWithCoins(coins2, 14);
            Console.WriteLine("pocet minci: {0}", count);

            int[] coins3 = { 50, 49, 48, 47, 46, 45, 44 }; //b)

            count = PayWithCoins(coins3, 51);
            Console.WriteLine("pocet minci: {0}", count);

            Console.ReadKey();
        }
    }
}
