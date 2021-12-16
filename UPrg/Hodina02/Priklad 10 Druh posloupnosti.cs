using System;
// Tento zdrojovy kod jsem vypracoval zcela samostatne bez cizi pomoci
// Neokopiroval jsem ani neopsal jsem cizi zdrojove kody
// Nikdo mi pri vypracovani neradil
// Pokud nektery radek porusuje toto pravidlo je oznacen komentarem
// NENI MOJE TVORBA
// Poruseni techto pravidel se povazuje za podvod, ktery lze potrestat VYLOUCENIM ZE STUDIA
// Alexej Fedorenko, učo 37676 
namespace Priklad_10_Druh_posloupnosti
{
    class Program
    {
        static void Main(string[] args)
        {
            int num = 0;
            int prevNum = -1;
            int nCount = 0;
            string text = "";

            while(true)
            {
                Console.Write("Zadejte cislo: ");
                num = Convert.ToInt32(Console.ReadLine());
                if (num == 0)
                    break;

                if (nCount < 1)
                    text = "kratka";
                else if (text == "neni monotonni")
                    continue;
                else if (num > prevNum && (text == "nerostouci" || text == "klesajici") || num < prevNum && (text == "rostouci" || text == "neklesajici"))
                    text = "neni monotonni";
                else if (prevNum == num && text == "kratka")
                    text = "konstatni";
                else if (prevNum < num && text == "konstatni" || prevNum == num && text == "rostouci")
                    text = "neklesajici";
                else if (prevNum > num && text == "konstatni" || prevNum == num && text == "klesajici")
                    text = "nerostouci";
                else if (prevNum < num && text != "neklesajici")
                    text = "rostouci";
                else if (prevNum > num && text != "nerostouci")
                    text = "klesajici";


                prevNum = num;
                nCount++;
            }

            Console.WriteLine("Posloupnost je {0}", text);
            Console.ReadKey();

        }
    }
}
