using System;
// Tento zdrojovy kod jsem vypracoval zcela samostatne bez cizi pomoci
// Neokopiroval jsem ani neopsal jsem cizi zdrojove kody
// Nikdo mi pri vypracovani neradil
// Pokud nektery radek porusuje toto pravidlo je oznacen komentarem
// NENI MOJE TVORBA
// Poruseni techto pravidel se povazuje za podvod, ktery lze potrestat VYLOUCENIM ZE STUDIA
// Alexej Fedorenko, učo 37676 
namespace Priklad_01_Dlouha_cela_cisla
{
    class Program
    {
        const int MAX_LENGTH = 100;
        static short[] zero = new short[MAX_LENGTH];
        static short[] ten = CreateBigEndianNumber("10");

        //pomocne funkce
        static int FindStartOfBigEndianNumber(short[] number)
        {
            for (int i = 0; i < number.Length; i++)
            {
                if (number[i] != 0)
                    return i;
            }
            return number.Length;
        }

        static string BigEndianNumberToString(short[] number)
        {
            string text = "";
            int start = FindStartOfBigEndianNumber(number);

            if (start == number.Length)
                text = "0";

            for (int i = start; i < number.Length; i++)
                text += number[i].ToString();

            return text;
        }

        static short[] BigEndianCreateAbs(short[] number)
        {
            short[] abs = new short[MAX_LENGTH];
            for (int i = 0; i < number.Length; i++)
            {
                if (number[i] < 0)
                    abs[i] = (short)(number[i] * -1);
                else
                    abs[i] = number[i];
            }
            return abs;
        }

        static short[] BigEndianCreateCopy(short[] number)
        {
            short[] copy = new short[MAX_LENGTH];
            for (int i = 0; i < number.Length; i++)
            {
                if (number[i] != 0)
                    copy[i] = number[i];
            }
            return copy;
        }

        //cviceni
        static short[] CreateBigEndianNumber(string s) //a)
        {
            short[] number = new short[MAX_LENGTH];
            bool negative = false;
            for (int i = 0; i < s.Length; i++)
            {
                short num = (short)(s[i] - '0');
                if (i == 0 && s[i] == '-')
                {
                    negative = true;
                    continue;
                }
                else if (num < 0 && num > 9)
                    continue;
                if (negative)
                {
                    num *= -1;
                    negative = false;
                }
                number[MAX_LENGTH - s.Length + i] = num;
            }

            return number;
        }

        static void WriteBigEndianNumber(short[] number) //b)
        {
            Console.WriteLine(BigEndianNumberToString(number));
        }

        static int BigEndianCompare(short[] a, short[] b) //c)
        {
            for (int i = 0; i < MAX_LENGTH; i++)
            {
                if (a[i] > b[i])
                    return 1;
                else if (a[i] < b[i])
                    return -1;
            }
            return 0;
        }

        static short[] BigEndianSum(short[] a, short[] b) //d)
        {
            if (BigEndianCompare(a, zero) == 0)
                return BigEndianCreateCopy(b);
            else if (BigEndianCompare(b, zero) == 0)
                return BigEndianCreateCopy(a);

            short shift = 0;
            short[] sum = null;

            int aCmp = BigEndianCompare(a, zero);
            int bCmp = BigEndianCompare(b, zero);

            if (aCmp == -1)
            {
                if (bCmp == -1)
                {
                    sum = BigEndianSum(BigEndianCreateAbs(a), BigEndianCreateAbs(b));
                    sum[FindStartOfBigEndianNumber(sum)] *= -1;
                    return sum;
                }           
                else
                    return BigEndianMinus(b, BigEndianCreateAbs(a));
            }
            else if (bCmp == -1)
                return BigEndianMinus(a, BigEndianCreateAbs(b));
            
            sum = new short[MAX_LENGTH];

            for (int i = a.Length - 1; i >= 0; i--)
            {
                sum[i] = (short)(a[i] + b[i] + shift);
                shift = (short)(sum[i] / 10);
                sum[i] %= 10;
            }
            return sum;
        }
        static short[] BigEndianMinus(short[] a, short[] b) //e)
        {
            if (BigEndianCompare(b, zero) == 0)
                return BigEndianCreateCopy(a);

            short shift = 0;
            short[] minus = null;

            int bCmp = BigEndianCompare(b, zero);
            int aCmp = BigEndianCompare(a, zero);     

            if (bCmp == -1)
            {
                if (aCmp == -1)
                    return BigEndianMinus(BigEndianCreateAbs(b), BigEndianCreateAbs(a));
                else
                    return BigEndianSum(a, BigEndianCreateAbs(b));
            }
            else if (aCmp == -1)
            {
                minus = BigEndianSum(BigEndianCreateAbs(a), b);
                minus[FindStartOfBigEndianNumber(minus)] *= -1;
                return minus;
            }

            minus = new short[MAX_LENGTH];

            short[] biggest = a;
            short[] smallest = b;

            if (BigEndianCompare(a, b) == -1)
            {
                biggest = b;
                smallest = a;
            }

            for (int i = a.Length - 1; i >= 0; i--)
            {
                minus[i] = (short)(biggest[i] - smallest[i] + shift);
                if (minus[i] < 0)
                {
                    shift = -1;
                    minus[i] += 10;
                }
                else
                    shift = 0;
            }

            if (biggest == b)
                minus[FindStartOfBigEndianNumber(minus)] *= -1;

            return minus;
        }

        static short[] BigEndianMultiply(short[] a, short[] b) //f)
        {
            short[] multiply = new short[MAX_LENGTH];

            if (BigEndianCompare(a, zero) == 0)
                return multiply;
            else if (BigEndianCompare(b, zero) == 0)
                return multiply;

            short[] aAbsCopy = BigEndianCreateAbs(a);
            short[] bAbsCopy = BigEndianCreateAbs(b);

            int aCmp = BigEndianCompare(a, zero);
            int bCmp = BigEndianCompare(b, zero);

            for (int i = aAbsCopy.Length - 1; i >= 0; i--)
            {
                short shift = 0;
                for (int x = bAbsCopy.Length - 1; x >= 0; x--)
                {
                    int curIndex = i + (x - (bAbsCopy.Length - 1)); 
                    if (curIndex < 0) 
                        break;

                    multiply[curIndex] += (short)(aAbsCopy[i] * bAbsCopy[x] + shift);
                    shift = (short)(multiply[curIndex] / 10);
                    multiply[curIndex] %= 10;
                }
            }

            if (aCmp == -1 && bCmp == 1 || bCmp == -1 && aCmp == 1)
                multiply[FindStartOfBigEndianNumber(multiply)] *= -1;
            return multiply;
        }

        static short[] BigEndianDivision(short[] a, short[] b) //g)
        {
            short[] division = new short[MAX_LENGTH];
            string bText = BigEndianNumberToString(b);
            string aText = BigEndianNumberToString(a);

            if (aText == "0")
                return division;
            else if (bText == "0")
                return division;
            else if (bText == "1")
                return a;

            int aCmp = BigEndianCompare(a, zero);
            int bCmp = BigEndianCompare(b, zero);

            if (aCmp == -1 && bCmp == 1)
            {
                division = BigEndianDivision(BigEndianCreateAbs(a), b);
                division[FindStartOfBigEndianNumber(division)] *= -1;
                return division;
            }
            else if (bCmp == -1 && aCmp == 1 || bText == "-1")
            {
                division = BigEndianDivision(a, BigEndianCreateAbs(b));
                division[FindStartOfBigEndianNumber(division)] *= -1;
                return division;
            }
            else if (bCmp == -1 && aCmp == -1)
            {
                division = BigEndianDivision(BigEndianCreateAbs(a), BigEndianCreateAbs(b));
                return division;
            }

            short[] aCopy = BigEndianCreateCopy(a);
            short[] bCopy = BigEndianCreateCopy(b);
            short[] aPreMinusCopy = BigEndianCreateCopy(a);

            bool exit = false;
            int bigEndianEnd = MAX_LENGTH - 1;
            short divisionMultiplier = 0;

            while (!exit)
            {
                bCopy = BigEndianMultiply(bCopy, ten);
                if (BigEndianCompare(BigEndianMinus(a, bCopy), zero) == -1)
                {
                    exit = true;
                    continue;
                }
                divisionMultiplier++;
            }

            bCopy = BigEndianCreateCopy(b);
            for (int i = 0; i < divisionMultiplier; i++)
                bCopy = BigEndianMultiply(bCopy, ten);

            exit = false;
            bigEndianEnd -= divisionMultiplier;

            while (!exit)
            {
                aCopy = BigEndianMinus(aCopy, bCopy);

                if (BigEndianCompare(aCopy, zero) == -1)
                {
                    if (divisionMultiplier != 0)
                    {
                        divisionMultiplier--;
                        bCopy = BigEndianCreateCopy(b);
                        for (int i = 0; i < divisionMultiplier; i++)
                            bCopy = BigEndianMultiply(bCopy, ten);

                        bigEndianEnd = MAX_LENGTH - 1 - divisionMultiplier;
                        aCopy = aPreMinusCopy;
                        continue;
                    }
                    exit = true;
                    continue;
                }
                division[bigEndianEnd]++;
                aPreMinusCopy = BigEndianCreateCopy(aCopy);
            }
            return division;
        }

        static void Main(string[] args)
        {
            short[] c1 = CreateBigEndianNumber("560111202232646"); 
            short[] c2 = CreateBigEndianNumber("560100600690986");
            short[] c3 = BigEndianSum(c1, c2);
            short[] c4 = BigEndianMinus(c1, c2);
            short[] c5 = BigEndianMultiply(c1, c4);
            short[] c6 = BigEndianDivision(c1, c4);
            int cmp = BigEndianCompare(c1, c2);

            Console.Write("BigEndian Number: ");
            WriteBigEndianNumber(c1);

            Console.Write("Compare: ");
            Console.WriteLine(cmp);

            Console.Write("Sum: ");
            WriteBigEndianNumber(c3);

            Console.Write("Minus: ");
            WriteBigEndianNumber(c4);

            Console.Write("Multiply: ");
            WriteBigEndianNumber(c5);

            Console.Write("Division: ");
            WriteBigEndianNumber(c6);


            Console.ReadKey();
        }
    }
}
