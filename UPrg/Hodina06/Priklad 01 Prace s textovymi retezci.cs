using System;
// Tento zdrojovy kod jsem vypracoval zcela samostatne bez cizi pomoci
// Neokopiroval jsem ani neopsal jsem cizi zdrojove kody
// Nikdo mi pri vypracovani neradil
// Pokud nektery radek porusuje toto pravidlo je oznacen komentarem
// NENI MOJE TVORBA
// Poruseni techto pravidel se povazuje za podvod, ktery lze potrestat VYLOUCENIM ZE STUDIA
// Alexej Fedorenko, učo 37676 
namespace Priklad_01_Prace_s_textovymi_retezci
{
    class Program
    {
        static int UniqueLetters(string text)               // a)
        {
            bool[] occurence = new bool[25];
            int occurenceCount = 0;

            for (int i = 0; i < text.Length; i++)
            {
                int pos = char.ToUpper(text[i]) - 0x41;
                if (pos >= 0 && pos <= 25)
                {
                    if (occurence[pos] != true)
                    {
                        occurence[pos] = true;
                        occurenceCount++;
                    }
                    else
                        if (!occurence[pos])
                            occurence[pos] = true;
                }
            }

            return occurenceCount;
        }

        static int WordCount(string text)                   // b)
        {
            int count = 0;

            for (int i = 0; i < text.Length; i++)
            {
                if (char.IsLetter(text[i]))
                {
                    for (; i < text.Length && char.IsLetter(text[i]); i++);
                    count++;
                }
                else if (!char.IsWhiteSpace(text[i]))
                    for (; i < text.Length && !char.IsWhiteSpace(text[i]); i++);
            }

            return count;
        }

        static string FirstWord(string text, int startPos) // c)
        {
            string word = "";

            if (startPos < 0)
                return word;

            for (int i = startPos; i < text.Length; i++)
            {
                if (char.IsLetter(text[i]))
                {
                    for (int x = i - 1; x >= 0 && char.IsLetter(text[x]); x--)
                        word = text[x] + word;
                            
                    for (; i < text.Length && char.IsLetter(text[i]); i++)
                        word += text[i];
                    break;
                }
                else if (!char.IsWhiteSpace(text[i]))
                    for (; i < text.Length && !char.IsLetter(text[i]); i++);
            }
            return word;
        }

        static string LongestWord(string text)              // d)
        {
            string longestWord = "";

            for (int i = 0; i < text.Length; i++)
            {
                if (!char.IsLetter(text[i])) 
                    continue;

                string word = FirstWord(text, i);
                for (; i < text.Length && char.IsLetter(text[i]); i++);

                if (longestWord == "")
                    longestWord = word;
                else if (word.Length > longestWord.Length)
                    longestWord = word;
            }

            return longestWord;
        }

        static string LexicalyLongestWord(string text)         // e)
        {
            string longestWord = "";

            for (int i = 0; i < text.Length; i++)
            {
                if (!char.IsLetter(text[i])) 
                    continue;

                string word = FirstWord(text, i);
                for (; i < text.Length && char.IsLetter(text[i]); i++) ;

                if (longestWord == "")
                    longestWord = word;
                else if (word.Length > longestWord.Length || char.ToUpper(word[0]) > char.ToUpper(longestWord[0]))
                    longestWord = word;
            }


            return longestWord;
        }

        static string MostCommonWord(string text) //f)
        {
            int count = 0, occurenceCount = 0;
            string[] words = new string[WordCount(text)];
            string mostCommonWord = "";
            
            for (int i = 0; i < text.Length; i++)
            {
                if (!char.IsLetter(text[i])) 
                    continue;

                string word = FirstWord(text, i);
                for (; i < text.Length && char.IsLetter(text[i]); i++) ;

                if (word != "")
                    words[count++] = word;
            }
            
            for (int i = 0; i < words.Length; i++)
            {
                int tempOccurenceCount = 0;

                if (mostCommonWord != words[i])
                {
                    for (int x = i + 1; x < words.Length; x++)
                    {
                        if (words[i] == words[x])
                            tempOccurenceCount++;
                    }

                    if (tempOccurenceCount > occurenceCount)
                    {
                        occurenceCount = tempOccurenceCount;
                        mostCommonWord = words[i];
                    }
                }
            }

            for (int i = 0; i < words.Length; i++)
            {
                int tempOccurenceCount = 0;
                if (mostCommonWord != words[i])
                {
                    for (int x = i + 1; x < words.Length; x++)
                    {
                        if (words[i] == words[x])
                            tempOccurenceCount++;
                    }

                    if (tempOccurenceCount == occurenceCount)
                    {
                        mostCommonWord = "";
                        break;
                    }
                }
            }

            return mostCommonWord;
        }

        static void Main(string[] args)
        {
            string s1 = "Alena ma 2 ruce.";
            int uniqueLetters = UniqueLetters(s1);
            int wordCount = WordCount(s1);
            string firstWord = FirstWord(s1, 2);
            string firstWord2 = FirstWord(s1, s1.Length - 1);
            string longestWord = LongestWord(s1);
            string lexicalyLongestWord = LexicalyLongestWord(s1);
            string s2 = "Mama ma 2 ruce a v ruce hul";
            string mostCommonWord = MostCommonWord(s1 + s2);

            Console.WriteLine("Pocet různých pismen: {0}", uniqueLetters);
            Console.WriteLine("PocetSlov: {0}",            wordCount);
            Console.WriteLine("Prvni slovo: {0}",          firstWord);
            Console.WriteLine("Prvni slovo2: {0}",         firstWord2);
            Console.WriteLine("Nejdelsi slovo: {0}",       longestWord);
            Console.WriteLine("Nejvetsi slovo: {0}",       lexicalyLongestWord);
            Console.WriteLine("Nejcastejsi slovo: {0}",    mostCommonWord);

            Console.ReadKey();
        }
    }
}
