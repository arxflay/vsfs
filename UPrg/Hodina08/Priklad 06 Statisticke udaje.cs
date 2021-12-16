using System;
using System.IO;
// Tento zdrojovy kod jsem vypracoval zcela samostatne bez cizi pomoci
// Neokopiroval jsem ani neopsal jsem cizi zdrojove kody
// Nikdo mi pri vypracovani neradil
// Pokud nektery radek porusuje toto pravidlo je oznacen komentarem
// NENI MOJE TVORBA
// Poruseni techto pravidel se povazuje za podvod, ktery lze potrestat VYLOUCENIM ZE STUDIA
// Alexej Fedorenko, učo 37676 
namespace Priklad_06_Statisticke_udaje
{
    class Program
    {
        static int UniqueLetterCount(string filename) // a)
        {
            if (!File.Exists(filename))
                return 0;

            int countUnique = 0;
            StreamReader fileReader = new StreamReader(filename);
            char[] count = new char[char.MaxValue];
            string line = "";

            while ((line = fileReader.ReadLine()) != null)
                for (int i = 0; i < line.Length; i++)
                    if (count[line[i]] == 0)
                        count[line[i]] = (char)1;

            fileReader.Close();

            for (int i = 0; i < count.Length; i++)
                if (count[i] == 1)
                    ++countUnique;

            return countUnique;
        }

        static int WordCount(string filename) // b)
        {
            if (!File.Exists(filename))
                return 0;

            int wordCount = 0;
            StreamReader fileReader = new StreamReader(filename);
            string line = "";

            while ((line = fileReader.ReadLine()) != null)
            {
                string[] words = line.Split(' ');
                for (int i = 0; i < words.Length; i++)
                {
                    char[] word = words[i].ToCharArray();
                    for (int j = 0; j < word.Length; j++)
                    {
                        if (char.IsLetter(word[j]))
                        {
                            wordCount++;
                            break;
                        }
                    }
                }

            }
            fileReader.Close();

            return wordCount;
        }

        static void Main(string[] args)
        {
            Console.WriteLine("unique count {0}", UniqueLetterCount("aaa.txt"));
            Console.WriteLine("word count {0}", WordCount("aaa.txt"));
            Console.ReadKey();
        }
    }
}
