using System;
// Tento zdrojovy kod jsem vypracoval zcela samostatne bez cizi pomoci
// Neokopiroval jsem ani neopsal jsem cizi zdrojove kody
// Nikdo mi pri vypracovani neradil
// Pokud nektery radek porusuje toto pravidlo je oznacen komentarem
// NENI MOJE TVORBA
// Poruseni techto pravidel se povazuje za podvod, ktery lze potrestat VYLOUCENIM ZE STUDIA
// Alexej Fedorenko, učo 37676 
namespace Priklad_07_Pocet_dni_po_datu
{
    class Program
    {
        struct Date
        {
            public int day;
            public int month;
            public int year;
        }

        static bool IsLeapYear(int year)
        {
            if (year % 4 != 0) 
                return false;
            if (year % 100 != 0) 
                return true;
            if (year % 400 != 0)
                return false;

            return true;
        }

        static long DateToNumber(Date date)
        {
            long number = date.day;

            for (int i = 1900; i < date.year; i++)
            {
                number += 365;
                if (IsLeapYear(i)) number++;
            }

            for (int i = 1; i < date.month; i++)
            {
                switch (i)
                {
                    case 4:
                    case 6:
                    case 9:
                    case 11:
                        number += 30;
                        break;
                    case 2:
                        number += 28;
                        if (IsLeapYear(date.year)) number++;
                        break;
                    default:
                        number += 31;
                        break;
                }
            }

            return number;
        }

        static Date NumberToDate(long number)
        {
            bool is28DaysMonth = false;
            bool is31DaysMonth = true;
            bool is30DaysMonth = false;
            Date date;
            date.year = 1900; date.month = 1; date.day = 0;

            while (number > 366 && IsLeapYear(date.year) || number > 365  && !IsLeapYear(date.year))
            {
                number -= 365;
                if (IsLeapYear(date.year)) --number;
                ++date.year;
            }

            while (number > 28 && is28DaysMonth && IsLeapYear(date.year) || number > 29 && is28DaysMonth && !IsLeapYear(date.year) ||  number > 30 && is30DaysMonth || number > 31 && is31DaysMonth)
            {
                if (is30DaysMonth)
                    number -= 30;
                else if (is28DaysMonth)
                {
                    number -= 28;
                    if (IsLeapYear(date.year)) --number;
                }
                else
                    number -= 31;

                date.month++;
                is30DaysMonth = date.month == 4 || date.month == 6 || date.month == 9 || date.month == 11;
                is28DaysMonth = date.month == 2;
                is31DaysMonth = date.month != 4 || date.month != 6 || date.month != 9 || date.month != 11 || date.month != 2;
            }
            date.day = (int)number;

            return date;
        }

        static Date NextDate(Date date, int days)
        {
            long numberDate = DateToNumber(date) + days;

            return NumberToDate(numberDate);
        }

        static void Main(string[] args)
        {
            Date d;

            d.day = 1; d.month = 1; d.year = 2013; //common year + 364 test
            Date d1 = NextDate(d, 364);
            Console.WriteLine("common year + 364 test = {0}.{1}.{2}", d1.day, d1.month, d1.year);

            d1 = NextDate(d, 365); //common year + 365 test
            Console.WriteLine("common year + 365 test = {0}.{1}.{2}", d1.day, d1.month, d1.year);

            d.day = 1; d.month = 1; d.year = 2016; //leap year + 365 test
            d1 = NextDate(d, 365);
            Console.WriteLine("leap year + 365 test = {0}.{1}.{2}", d1.day, d1.month, d1.year);

            d1 = NextDate(d, 366); //leap year + 366 test
            Console.WriteLine("leap year + 366 test = {0}.{1}.{2}", d1.day, d1.month, d1.year);

            d.day = 16; d.month = 7; d.year = 2015; //common year + 500 test
            d1 = NextDate(d, 500);
            Console.WriteLine("common year + 500 test = {0}.{1}.{2}", d1.day, d1.month, d1.year);

            Console.ReadKey();
        }
    }
}
