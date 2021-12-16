using System;
using System.IO;
// Tento zdrojovy kod jsem vypracoval zcela samostatne bez cizi pomoci
// Neokopiroval jsem ani neopsal jsem cizi zdrojove kody
// Nikdo mi pri vypracovani neradil
// Pokud nektery radek porusuje toto pravidlo je oznacen komentarem
// NENI MOJE TVORBA
// Poruseni techto pravidel se povazuje za podvod, ktery lze potrestat VYLOUCENIM ZE STUDIA
// Alexej Fedorenko, učo 37676 
namespace Priklad_01_Nahodny_binarni_soubor
{
    class Program
    {
        static void RandomFile(string filename, int count)
        {
            Random prnd = new Random();
            FileStream fs = new FileStream(filename, FileMode.OpenOrCreate);
            BinaryWriter bw = new BinaryWriter(fs);

            for (int i = 0; i < count; i++)
                bw.Write(prnd.Next(0, int.MaxValue));

            bw.Close();
        }

        static void Main(string[] args)
        {
            RandomFile("cisla.dat", 1000);
        }
    }
}
