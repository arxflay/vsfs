// Tento zdrojovy kod jsem vypracoval zcela samostatne bez cizi pomoci
// Neokopiroval jsem ani neopsal jsem cizi zdrojove kody
// Nikdo mi pri vypracovani neradil
// Pokud nektery radek porusuje toto pravidlo je oznacen komentarem
// NENI MOJE TVORBA
// Poruseni techto pravidel se povazuje za podvod, ktery lze potrestat VYLOUCENIM ZE STUDIA
// Alexej Fedorenko, učo 37676 
using System;

namespace Priklad_04_Rimska_cisla
{
    class Program
    {
        static void ChangeSymbols(ref char firstSymbol, ref char midSymbol, ref char lastSymbol, int shift = 0)
        {
            if (shift == 0)
            {
                firstSymbol = 'I';
                midSymbol = 'V';
                lastSymbol = 'X';
            }
            else if (shift == 1)
            {
                firstSymbol = 'X';
                midSymbol = 'L';
                lastSymbol = 'C';
            }
            else if (shift == 2)
            {
                firstSymbol = 'C';
                midSymbol = 'D';
                lastSymbol = 'M';
            }
            else
            {
                firstSymbol = 'M';
                midSymbol = 'M';
                lastSymbol = 'M';
            }
        }

        static string DecToRoman(int number) //a)
        {

            int shift = 0;
            string text = "";
            string sign = "";
            int mCount = 1;

            if (number < 0)
            {
                number *= -1;
                sign = "-";
            }
           
            while (number > 0)
            {
                int remainder = number % 10;
                number /= 10;

                if (remainder != 0)
                {

                    if (shift == 3)
                    {
                        for (int i = 0; i < mCount * remainder; i++)
                            text = 'M' + text;
                        mCount *= 10;
                        continue;
                    }

                    char firstSymbol = '\0';
                    char midSymbol = '\0';
                    char lastSymbol = '\0';
                    string finalSymbol = "";

                    ChangeSymbols(ref firstSymbol, ref midSymbol, ref lastSymbol, shift);

                    switch (remainder)
                    {
                        case 1:
                        case 2:
                        case 3:
                        case 4:
                        case 9:
                            finalSymbol = firstSymbol + finalSymbol;
                            if (remainder <= 3)
                                for (int i = 1; i < remainder; i++)
                                    finalSymbol = firstSymbol + finalSymbol;
                            else if (remainder == 4)
                                finalSymbol += midSymbol;
                            else if (remainder == 9)
                                finalSymbol += lastSymbol;
                            break;
                        case 5:
                        case 6:
                        case 7:
                        case 8:
                            finalSymbol = midSymbol.ToString();
                            for (int i = 5; i < remainder; i++)
                                finalSymbol += firstSymbol;
                            break;
                    }
                    text = finalSymbol + text;
                }
                shift++;
            }

            return sign + text;
        }

        //such an ugly function but it works
        static int RomanToDec(string text) //b) 
        {
            int symbolShift = 0;
            int numberShift = 1;
            int number = 0;
            string temptext = text.ToUpper();
            for (int i = temptext.Length - 1; i >= 0; i--)
            {
                char firstSymbol = '\0';
                char midSymbol = '\0';
                char lastSymbol = '\0';

                ChangeSymbols(ref firstSymbol, ref midSymbol, ref lastSymbol, symbolShift);

                if (i == 0 && temptext[i] == '-')
                    number *= -1;
                else if (symbolShift == 3)
                {
                    if (text[i] != 'M') //fix for incorrect format
                        break;

                    while (i > -1 && text[i] == 'M')
                    {
                        number += 1000;
                        i--;
                    }
                    i++;
                }
                else if (temptext[i] == firstSymbol)
                {
                    int j = 1;

                    while (i - j >= 0 && j < 3 && temptext[i - j] == firstSymbol)
                        j++;

                    i -= (j - 1);
                    if (i > 0 && temptext[i - 1] == midSymbol)
                    {
                        j += 5;
                        i--;
                    }

                    number += j * numberShift;
                }
                else if (temptext[i] == midSymbol)
                {
                    if ((i - 1) > -1 && temptext[i - 1] == firstSymbol)
                    {
                        number += 4 * numberShift;
                        i--;
                    }
                    else
                        number += 5 * numberShift;
                }
                else if (temptext[i] == lastSymbol && (i - 1) > -1 && temptext[i - 1] == firstSymbol)
                {
                    number += 9 * numberShift;
                    i--;
                }
                else
                    i++;

                numberShift *= 10;
                symbolShift++;
            }

            return number;
        }

        static void Main(string[] args)
        {
            string romanNum = "";
            int num = 0;

            Console.WriteLine("Start Test -> Positive DecToRoman, RomanToDec");
            for (int i = 0; i < 10000; i++)
            {
                romanNum = DecToRoman(i);
                num = RomanToDec(romanNum);
                if (num != i)
                    Console.WriteLine("from {0} to {1} with value {3} != {0}", i, romanNum, num);
            }
            Console.WriteLine("End Test");

            Console.WriteLine("Start Test -> Negative DecToRoman, RomanToDec");
            for (int i = -10000; i >= 0; i++)
            {
                romanNum = DecToRoman(i);
                num = RomanToDec(romanNum);
                if (num != i)
                    Console.WriteLine("from {0} to {1} with value {3} != {0}", i, romanNum, num);
            }
            Console.WriteLine("End Test");

            Console.WriteLine("Start Test -> Incorrect RomanFormat format");
            RomanToDec("TEST");
            RomanToDec("IXIXIXIXIXI");
            Console.WriteLine("End Test");

            Console.ReadKey();
        }
    }
}
