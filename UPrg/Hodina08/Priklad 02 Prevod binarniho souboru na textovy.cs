using System;
using System.IO;
// Tento zdrojovy kod jsem vypracoval zcela samostatne bez cizi pomoci
// Neokopiroval jsem ani neopsal jsem cizi zdrojove kody
// Nikdo mi pri vypracovani neradil
// Pokud nektery radek porusuje toto pravidlo je oznacen komentarem
// NENI MOJE TVORBA
// Poruseni techto pravidel se povazuje za podvod, ktery lze potrestat VYLOUCENIM ZE STUDIA
// Alexej Fedorenko, učo 37676 
namespace Priklad_02_Prevod_binarniho_souboru_na_textovy
{
    class Program
    {
        const int MAX_LINE_LENGTH = 10;
        static void BinaryToText(string binFilename, string textFilename)
        {
            if (!File.Exists(binFilename))
                return;

            FileStream binfile = new FileStream(binFilename, FileMode.Open);
            BinaryReader binfileReader = new BinaryReader(binfile);
            StreamWriter textFile = new StreamWriter(textFilename);

            long eof = binfile.Seek(0, SeekOrigin.End);
            binfile.Seek(0, SeekOrigin.Begin);
            long count = eof / sizeof(Int32);

            int lineLength = 0;

            for (int i = 0; i < count; i++)
            {            
                if (lineLength == 9 || i == count - 1)
                {
                    textFile.WriteLine(binfileReader.ReadInt32());
                    lineLength = 0;
                }
                else
                    textFile.Write(binfileReader.ReadInt32() + " ");

                ++lineLength;
            }

            binfileReader.Close();
            textFile.Close();

        }
        static void Main(string[] args)
        {
            BinaryToText("cisla.dat", "cisla.txt");
        }
    }
}
