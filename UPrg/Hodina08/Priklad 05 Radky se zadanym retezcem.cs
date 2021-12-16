using System.IO;
// Tento zdrojovy kod jsem vypracoval zcela samostatne bez cizi pomoci
// Neokopiroval jsem ani neopsal jsem cizi zdrojove kody
// Nikdo mi pri vypracovani neradil
// Pokud nektery radek porusuje toto pravidlo je oznacen komentarem
// NENI MOJE TVORBA
// Poruseni techto pravidel se povazuje za podvod, ktery lze potrestat VYLOUCENIM ZE STUDIA
// Alexej Fedorenko, učo 37676
namespace Priklad_05_Radky_se_zadanym_retezcem
{
    class Program
    {
        static void WriteAllRowsContains(string filenameFrom, string filenameTo, string text)
        {
            if (!File.Exists(filenameFrom))
                return;
            StreamReader fromReader = new StreamReader(filenameFrom);
            StreamWriter toWriter = new StreamWriter(filenameTo);

            string line = "";

            while ((line = fromReader.ReadLine()) != null)
                if (line.ToLower().Contains(text.ToLower()))
                    toWriter.WriteLine(line);

            fromReader.Close();
            toWriter.Close();
        }
        static void Main(string[] args)
        {
            WriteAllRowsContains("aaa.txt", "bbb.txt", "dnes");
        }
    }
}
