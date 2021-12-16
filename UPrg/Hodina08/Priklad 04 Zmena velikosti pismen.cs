using System.IO;
// Tento zdrojovy kod jsem vypracoval zcela samostatne bez cizi pomoci
// Neokopiroval jsem ani neopsal jsem cizi zdrojove kody
// Nikdo mi pri vypracovani neradil
// Pokud nektery radek porusuje toto pravidlo je oznacen komentarem
// NENI MOJE TVORBA
// Poruseni techto pravidel se povazuje za podvod, ktery lze potrestat VYLOUCENIM ZE STUDIA
// Alexej Fedorenko, učo 37676 
namespace Priklad_04_Zmena_velikosti_pismen
{
    class Program
    {
        static void ChangeLettersSize(string filenameFrom, string filenameTo)
        {
            if (!File.Exists(filenameFrom))
                return;

            StreamReader fromReader = new StreamReader(filenameFrom);
            StreamWriter toWriter = new StreamWriter(filenameTo);

            string line = "";
            bool first = true;

            while ((line = fromReader.ReadLine()) != null)
            {
                if (first)
                {
                    line = line.ToUpper();
                    first = false;
                }
                else if (line.Length > 0)
                {
                    string[] words = line.Split(' ');
                    for (int x = 0; x < words.Length; x++)
                    {
                        if (words[x].Length >= 3)
                            words[x] = words[x].Substring(0, 1).ToUpper() + words[x].Substring(1, words[x].Length - 1);
                    }

                    line = "";
                    for (int j = 0; j < words.Length; j++)
                        line += words[j] + " ";

                    line = line.TrimEnd();
                }
                toWriter.WriteLine(line);
            }
            fromReader.Close();
            toWriter.Close();
        }
        static void Main(string[] args)
        {
            ChangeLettersSize("aaa.txt", "novy.txt");
        }
    }
}
