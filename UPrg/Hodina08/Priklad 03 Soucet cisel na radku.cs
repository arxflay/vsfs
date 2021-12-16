using System;
using System.IO;
// Tento zdrojovy kod jsem vypracoval zcela samostatne bez cizi pomoci
// Neokopiroval jsem ani neopsal jsem cizi zdrojove kody
// Nikdo mi pri vypracovani neradil
// Pokud nektery radek porusuje toto pravidlo je oznacen komentarem
// NENI MOJE TVORBA
// Poruseni techto pravidel se povazuje za podvod, ktery lze potrestat VYLOUCENIM ZE STUDIA
// Alexej Fedorenko, učo 37676 
namespace Priklad_03_Soucet_cisel_na_radku
{
    class Program
    {

        static void NumbersSum(string numbersFilename, string sumFilename)
        {
            if (!File.Exists(numbersFilename))
                return;

            StreamReader numbersReader = new StreamReader(numbersFilename);
            StreamWriter sumWriter = new StreamWriter(sumFilename, true);

            long sum = 0;
            string line = "";

            while((line = numbersReader.ReadLine()) != null)
            {
                line = line.Trim();
                string[] numbers = line.Split(' ');
                for (int i = 0; i < numbers.Length; i++)
                    sum += Convert.ToInt32(numbers[i]);
            }
            numbersReader.Close();

            sumWriter.WriteLine(sum);
            sumWriter.Close();
        }

        static void Main(string[] args)
        {
            NumbersSum("cisla.txt", "soucet.txt");
        }
    }
}
