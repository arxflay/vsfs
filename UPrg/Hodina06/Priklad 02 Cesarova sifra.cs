using System;
// Tento zdrojovy kod jsem vypracoval zcela samostatne bez cizi pomoci
// Neokopiroval jsem ani neopsal jsem cizi zdrojove kody
// Nikdo mi pri vypracovani neradil
// Pokud nektery radek porusuje toto pravidlo je oznacen komentarem
// NENI MOJE TVORBA
// Poruseni techto pravidel se povazuje za podvod, ktery lze potrestat VYLOUCENIM ZE STUDIA
// Alexej Fedorenko, učo 37676 
namespace Priklad_02_Cesarova_sifra
{
    class Program
    {
        static string CesarCipher(string text, int shift) // a)
        {
            string word = "";

            for (int i = 0; i < text.Length; i++)
                word += (char)(text[i] + shift);

            return word;
        }

        static void Main(string[] args)
        {
            string text = "Toto je tajny text: 1726";
            string crypted = CesarCipher(text, 20);
            string original = CesarCipher(crypted, -20);

            Console.WriteLine(crypted);
            Console.WriteLine(original);
            Console.ReadKey();
        }
    }
}
