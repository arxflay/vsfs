using System;
// Tento zdrojovy kod jsem vypracoval zcela samostatne bez cizi pomoci
// Neokopiroval jsem ani neopsal jsem cizi zdrojove kody
// Nikdo mi pri vypracovani neradil
// Pokud nektery radek porusuje toto pravidlo je oznacen komentarem
// NENI MOJE TVORBA
// Poruseni techto pravidel se povazuje za podvod, ktery lze potrestat VYLOUCENIM ZE STUDIA
// Alexej Fedorenko, učo 37676 
namespace Priklad_08_Den_v_tydnu
{
    class Program
    {
        enum Day
        {
            Pondeli = 1, Utery, Streda, Ctvrtek, Patek, Sobota, Nedele
        }

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

        static Day DayInWeek(Date date)
        {
            long numberDate = DateToNumber(date);

            while (numberDate > 7)
                numberDate -= 7;

            return (Day)numberDate;
        }

        static void Main(string[] args)
        {
            Date d;
            d.day = 15; d.month = 3; d.year = 1966;
            Day day = DayInWeek(d);
            Console.WriteLine(day);
            Console.ReadKey();
        }
    }
}
