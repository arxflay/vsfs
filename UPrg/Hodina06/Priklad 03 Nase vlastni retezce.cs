using System;
// Tento zdrojovy kod jsem vypracoval zcela samostatne bez cizi pomoci
// Neokopiroval jsem ani neopsal jsem cizi zdrojove kody
// Nikdo mi pri vypracovani neradil
// Pokud nektery radek porusuje toto pravidlo je oznacen komentarem
// NENI MOJE TVORBA
// Poruseni techto pravidel se povazuje za podvod, ktery lze potrestat VYLOUCENIM ZE STUDIA
// Alexej Fedorenko, učo 37676 
namespace Priklad_03_Nase_vlastni_retezce
{
    class Program
    {
        static int Compare(char[] s1, char[] s2) // a)
        {
            if (s1 == null || s2 == null)
                return -1;

            int maxLen = s1.Length;

            if (maxLen > s2.Length)
                maxLen = s2.Length;

            int cmp = 0;
            for (int i = 0; i < maxLen; i++)
            {
                if (s1[i] > s2[i])
                {
                    cmp = 1;
                    break;
                }
                else if (s1[i] < s2[i])
                {
                    cmp = -1;
                    break;
                }
            }

            if (cmp == 0 && s1.Length > s2.Length)
                cmp = 1;
            else if (cmp == 0 && s2.Length > s1.Length)
                cmp = -1;

            return cmp;
        }

        static int IndexOf(char[] s1, char[] s2, int start) // b)
        {
            int index = -1;

            if (s2.Length == 0 || start < 0 || s1 == null || s2 == null)
                return index;

            int shift = 0;
            for (int i = start; i < s1.Length; i++)
            {
                if (s1[i] == s2[shift])
                {
                    if (index == -1)
                        index = i;
                    shift++;
                }
                else
                {
                    index = -1;
                    shift = 0;
                }

                if (shift == s2.Length)
                    break;
            }

            if (shift != s2.Length)
                index = -1;

            return index;
        }

        static char[] Substring(char[] s1, int start, int length) //c)
        {
            char[] substring = null;

            if (start < 0 || start > (s1.Length - 1) || (s1.Length - start) < length || s1 == null)
                return substring;

            substring = new char[length];

            for (int i = start; i < start + length; i++)
                substring[i - start] = s1[i];

            return substring;
        }

        static char[] Insert(char[] s1, int start, char[] s2) //d)
        {
            char[] array = null;

            if (start > s1.Length || s1 == null || s2 == null)
                return array;

            array = new char[s1.Length + s2.Length];

            for (int i = 0; i < start; i++)
                array[i] = s1[i];

            for (int i = 0; i < s2.Length; i++)
                array[start + i] = s2[i];

            for (int i = start; i < s1.Length; i++)
                array[i + s2.Length] = s1[i];

            return array;
        }

        static char[] Remove(char[] s1, int start, int length) //e)
        {
            char[] array = null;

            if (start > s1.Length - 1 || start + length > s1.Length)
                return array;

            array = new char[s1.Length - length];

            for (int i = 0; i < start; i++)
                array[i] = s1[i];

            for (int i = start + length; i < s1.Length; i++)
                array[i - length] = s1[i];

            return array;
        }

        static char[] Replace(char[] s1, char[] s2, char[] s3) //f)
        {
            if (s1 == null || s2 == null || s1.Length == 0 || s2.Length == 0)
                return s1;

            int s2Ocurrence = 0;
            int[] s2index = new int[s1.Length / s2.Length];
            int shift = 0;

            for (int i = 0; i < s1.Length; i++)
            {
                if (s1[i] == s2[shift])
                    shift++;
                else
                    shift = 0;

                if (shift == s2.Length)
                {
                    shift = 0;
                    s2index[s2Ocurrence++] = i - (s2.Length - 1);
                }
            }
            int lenDifference = -(s2Ocurrence * s2.Length) + (s2Ocurrence * s3.Length);

            char[] array = new char[s1.Length + lenDifference];

            shift = 0;
            lenDifference = 0;
            for (int i = 0; i < array.Length; i++)
            {
                if (s2Ocurrence > shift && (i + lenDifference) == s2index[shift])
                {
                    for (; i + lenDifference < s2index[shift] + s3.Length; i++)
                        array[i] = s3[i  + lenDifference - s2index[shift]];
                    i--;
                    shift++;
                    lenDifference = -(shift * s3.Length) + (shift * s2.Length);
                }
                else
                    array[i] = s1[i - (shift * (s3.Length - 1))];
            }

            return array;
        }

        static void Main(string[] args)
        {
            char[] s1 = "klokan".ToCharArray();
            char[] s2 = "klobouk".ToCharArray();
            int cmp = Compare(s1, s2);
            int index = IndexOf(s2, "o".ToCharArray(), 3);
            char[] substring = Substring(s2, 2, 3);
            char[] insert = Insert(s1, 1, substring);
            char[] remove = Remove(s2, 3, 2);
            char[] replace = Replace(remove, "k".ToCharArray(), "".ToCharArray());
            Console.WriteLine("Compare s1 s2: {0}", cmp);
            Console.WriteLine("IndexOf \"o\" in s2: {0}", index);
            Console.WriteLine(substring);
            Console.WriteLine(insert);
            Console.WriteLine(remove);
            Console.WriteLine(replace);
            Console.ReadKey();
        }
    }
}
