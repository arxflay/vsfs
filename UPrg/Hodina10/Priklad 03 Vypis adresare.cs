// Tento zdrojovy kod jsem vypracoval zcela samostatne bez cizi pomoci
// Neokopiroval jsem ani neopsal jsem cizi zdrojove kody
// Nikdo mi pri vypracovani neradil
// Pokud nektery radek porusuje toto pravidlo je oznacen komentarem
// NENI MOJE TVORBA
// Poruseni techto pravidel se povazuje za podvod, ktery lze potrestat VYLOUCENIM ZE STUDIA
// Alexej Fedorenko, učo 37676 
using System;
using System.IO;

namespace Priklad_03_Vypis_adresare
{
    class Program
    {
        private static void WriteAllFiles(string path, string file)
        {
            StreamWriter logWriter = new StreamWriter(file);
            WriteAllFilesRec(path, logWriter);
            logWriter.Close();
        }

        private static void WriteAllFilesRec(string path, StreamWriter logWriter)
        {
            string[] files = Directory.GetFiles(path);
            string[] dirs = Directory.GetDirectories(path);

            for (int i = 0; i < files.Length; i++)
                logWriter.WriteLine(Path.GetFullPath(files[i]));
            for (int i = 0; i < dirs.Length; i++)
                WriteAllFilesRec(dirs[i], logWriter);
        }

        private static void Main(string[] args)
        {
            WriteAllFiles(".", "log.txt");
        }
    }
}
