using System;
// Tento zdrojovy kod jsem vypracoval zcela samostatne bez cizi pomoci
// Neokopiroval jsem ani neopsal jsem cizi zdrojove kody
// Nikdo mi pri vypracovani neradil
// Pokud nektery radek porusuje toto pravidlo je oznacen komentarem
// NENI MOJE TVORBA
// Poruseni techto pravidel se povazuje za podvod, ktery lze potrestat VYLOUCENIM ZE STUDIA
// Alexej Fedorenko, učo 37676 

namespace Priklad_03_Zlomky
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

        static short[] CreateBigEndianNumber(string s)
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

        static int BigEndianCompare(short[] a, short[] b)
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

        static short[] BigEndianSum(short[] a, short[] b)
        {
            if (BigEndianCompare(a, zero) == 0)
                return BigEndianCreateCopy(a);
            else if (BigEndianCompare(b, zero) == 0)
                return BigEndianCreateCopy(b);

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
        static short[] BigEndianMinus(short[] a, short[] b) 
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

        static short[] BigEndianMultiply(short[] a, short[] b)
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

        static short[] BigEndianDivision(short[] a, short[] b)
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
        //pomocne funkce
        static void FractionMinusSignCorrection(ref Fraction f)
        {
            int dividentCmp = BigEndianCompare(f.divident, zero);
            int divisorCmp = BigEndianCompare(f.divisor, zero);

            if (dividentCmp == 1 && divisorCmp == -1 || dividentCmp == -1 && divisorCmp == -1)
            {
                f.divident[FindStartOfBigEndianNumber(f.divident)] *= -1;
                f.divisor[FindStartOfBigEndianNumber(f.divisor)] *= -1;
            }
        }
        static bool IsEqualsZero(short[] number)
        {
            return BigEndianCompare(number, zero) == 0;
        }
        static bool IsFractionEqualsZero(Fraction f)
        {
            return IsEqualsZero(f.divident) || IsEqualsZero(f.divisor);
        }

        struct Fraction
        {
            public short[] divident;
            public short[] divisor;
        }

        static Fraction CreateFraction(string number) //a)
        {
            Fraction fraction;
            fraction.divident = null; fraction.divisor = null;

            string[] stringfraction = number.Split('/');
            if (stringfraction.Length == 2)
            {
                fraction.divident = CreateBigEndianNumber(stringfraction[0].Trim());
                fraction.divisor = CreateBigEndianNumber(stringfraction[1].Trim());
                FractionMinusSignCorrection(ref fraction);
            }

            return fraction;
        }

        static void WriteFraction(Fraction fraction) //b)
        {
            Console.WriteLine("{0}/{1}", BigEndianNumberToString(fraction.divident), BigEndianNumberToString(fraction.divisor));
        }

        static void BasicFraction (ref Fraction fraction) //c)
        {
            if (IsFractionEqualsZero(fraction))
            {
                fraction.divident = BigEndianCreateCopy(zero);
                fraction.divisor = BigEndianCreateCopy(zero);
            }

            short[] divident = BigEndianCreateAbs(fraction.divident);
            short[] divisor = BigEndianCreateAbs(fraction.divisor);

            if (BigEndianCompare(divident, divisor) == -1)
            {
                short[] temp = divident;
                divident = divisor;
                divisor = temp;
            }

            if (BigEndianCompare(divident, zero) == 1)
            {
                while (BigEndianCompare(divisor, zero) == 1)
                {
                    short[] temp = divisor;
                   
                    short[] mod = BigEndianMultiply(BigEndianDivision(divident, divisor), divisor);
                    divisor = BigEndianMinus(divident, mod);
                    divident = temp;
                }
            }
            fraction.divident = BigEndianDivision(fraction.divident, divident);
            fraction.divisor = BigEndianDivision(fraction.divisor, divident);
        }

        static Fraction FractionSum(Fraction f1, Fraction f2) //d)
        {
            Fraction fraction;
            fraction.divident = null; fraction.divisor = null;

            if (IsFractionEqualsZero(f1) || IsFractionEqualsZero(f2))
            {
                fraction.divident = BigEndianCreateCopy(zero);
                fraction.divisor = BigEndianCreateCopy(zero);
            }
            else if (IsFractionEqualsZero(f1))
            {
                fraction.divident = BigEndianCreateCopy(f1.divident);
                fraction.divident = BigEndianCreateCopy(f1.divisor);
            }
            else if (IsFractionEqualsZero(f2))
            {
                fraction.divident = BigEndianCreateCopy(f2.divident);
                fraction.divident = BigEndianCreateCopy(f2.divisor);
            }
            else if (BigEndianCompare(f1.divisor, f2.divisor) == 0)
            {
                fraction.divident = BigEndianSum(f1.divident, f2.divident);
                fraction.divisor = f1.divisor;
            }
            else
            {
                short[] commonMultiple = BigEndianMultiply(f1.divisor, f2.divisor);
                short[] f1Multiplier = BigEndianDivision(commonMultiple, f1.divisor);
                short[] f1Divident = BigEndianMultiply(f1.divident, f1Multiplier);
                short[] f2Multiplier = BigEndianDivision(commonMultiple, f2.divisor);
                short[] f2Divident = BigEndianMultiply(f2.divident, f2Multiplier);

                fraction.divisor = commonMultiple;
                fraction.divident = BigEndianSum(f1Divident, f2Divident);

                FractionMinusSignCorrection(ref fraction);
                BasicFraction(ref fraction);
            }

            return fraction;
        }

        static Fraction FractionMultiply(Fraction f1, Fraction f2) //e)
        {
            Fraction fraction;
            fraction.divident = null; fraction.divisor = null;

            if (IsFractionEqualsZero(f1) || IsFractionEqualsZero(f2))
            {
                fraction.divident = BigEndianCreateCopy(zero);
                fraction.divisor = BigEndianCreateCopy(zero);
            }
            else
            {
                fraction.divident = BigEndianMultiply(f1.divident, f2.divident);
                fraction.divisor = BigEndianMultiply(f1.divisor, f2.divisor);

                FractionMinusSignCorrection(ref fraction);
                BasicFraction(ref fraction);
            }

            return fraction;
        }

        static Fraction FractionDivision(Fraction f1, Fraction f2) //f)
        {
            Fraction fraction;
            fraction.divident = null; fraction.divisor = null;

            if (IsFractionEqualsZero(f1) || IsFractionEqualsZero(f2))
            {
                fraction.divident = BigEndianCreateCopy(zero);
                fraction.divisor = BigEndianCreateCopy(zero);
            }
            else
            {
                fraction.divident = BigEndianMultiply(f1.divident, f2.divisor);
                fraction.divisor = BigEndianMultiply(f1.divisor, f2.divident);

                FractionMinusSignCorrection(ref fraction);
                BasicFraction(ref fraction);
            }

            return fraction;
        }


        static void Main(string[] args)
        {
            Fraction f1 = CreateFraction("-56890/1223366");
            Fraction f2 = CreateFraction("2565689841/2365");
            WriteFraction(f1);
            WriteFraction(f2);
            BasicFraction(ref f1);
            BasicFraction(ref f2);
            WriteFraction(f1);
            WriteFraction(f2);
            Fraction f3 = FractionSum(f1, f2);
            Fraction f4 = FractionMultiply(f1, f2);
            Fraction f5 = FractionDivision(f2, f1);
            WriteFraction(f3);
            WriteFraction(f4);
            WriteFraction(f5);
            Console.ReadKey();
        }
    }
}
