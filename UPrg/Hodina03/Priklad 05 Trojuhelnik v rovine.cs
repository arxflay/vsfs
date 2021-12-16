using System;
// Tento zdrojovy kod jsem vypracoval zcela samostatne bez cizi pomoci
// Neokopiroval jsem ani neopsal jsem cizi zdrojove kody
// Nikdo mi pri vypracovani neradil
// Pokud nektery radek porusuje toto pravidlo je oznacen komentarem
// NENI MOJE TVORBA
// Poruseni techto pravidel se povazuje za podvod, ktery lze potrestat VYLOUCENIM ZE STUDIA
// Alexej Fedorenko, učo 37676 
namespace Priklad_05_Trojuhelnik_v_rovine
{
    class Program
    {
        struct Point
        {
            public double x;
            public double y;
        }

        struct Triangle
        {
            public Point a;
            public Point b;
            public Point c;
        }

        static bool AreSame(double a, double b)                 // a)
        {
            double max = a, min = b;

            if (b > a)
            {
                max = b;
                min = a;
            }

            return Math.Abs(max - min) <= 10e-13;
        }

        static double LineLength(Point a, Point b)             // b)
        {
            double abX = b.x - a.x;
            double abY = b.y - a.y;

            double abLength = Math.Sqrt(Math.Pow(abX, 2) + Math.Pow(abY, 2));

            return abLength;
        }

        static bool IsTriangle(Point a, Point b, Point c)      // c)
        {
            double abLength = LineLength(a, b);
            double bcLength = LineLength(b, c);
            double caLength = LineLength(c, a);


            bool isAllPointsOnSameLine = a.x == b.x && a.x == c.x && a.y == b.y && a.y == c.y;
            bool isAnyLineLengthEqualsZero = AreSame(abLength, 0) || AreSame(bcLength, 0) || AreSame(caLength, 0);
            bool isAnyTwoSidesSumLessEqualThanOther = abLength + bcLength <= caLength ||  caLength + bcLength <= abLength || abLength + caLength <= bcLength;

            if (isAllPointsOnSameLine || isAnyLineLengthEqualsZero || isAnyTwoSidesSumLessEqualThanOther)
                return false;

            return true;

        }

        static double Perimiter(Triangle t)                  // d)
        {
            double abLength = LineLength(t.a, t.b);
            double bcLength = LineLength(t.b, t.c);
            double caLength = LineLength(t.c, t.a);

            return abLength + bcLength + caLength;
        }

        static bool IsRightAngledTriangle(Triangle t)        // e)
        {
            double abLength = LineLength(t.a, t.b);
            double bcLength = LineLength(t.b, t.c);
            double caLength = LineLength(t.c, t.a);

            double a = Math.Sqrt(Math.Pow(caLength, 2) - Math.Pow(bcLength, 2));
            double b = Math.Sqrt(Math.Pow(caLength, 2) - Math.Pow(abLength, 2));
            double c = Math.Sqrt(Math.Pow(abLength, 2) + Math.Pow(bcLength, 2));

            bool isA = AreSame(a, abLength);
            bool isB = AreSame(b, bcLength);
            bool isC = AreSame(c, caLength);

            return isA && isB && isC;
        }

        static void Main(string[] args)
        {
            Point b1, b2, b3, b4, b5, b6, b7;
            Triangle t1, t2;

            b1.x = 7.2;  b1.y = -2;
            b2.x = -2.9; b2.y = -6.23;
            b3.x = 2;    b3.y = 5;
            b4.x = -1;   b4.y = -2.5;
            b5.x = 3;    b5.y = 7.5;
            b6.x = 3;    b6.y = -2.6;
            b7.x = 5.2;  b7.y = -2.6;
            t1.a = b1; t1.b = b2; t1.c = b3;
            t2.a = b5; t2.b = b6; t2.c = b7;

            bool is1 = AreSame(5, 4.99999999999992);
            double lineLength = LineLength(b1, b2);
            bool is2 = IsTriangle(b1, b2, b3);
            bool is3 = IsTriangle(b4, b3, b5);
            double perimiter1 = Perimiter(t1);
            double perimiter2 = Perimiter(t2);
            bool is4 = IsRightAngledTriangle(t2);

            Console.WriteLine("{0}\n{1}\n{2}\n{3}\n{4}\n{5}\n{6}", is1, lineLength, is2, is3, perimiter1, perimiter2, is4);
            Console.ReadKey();
        }
    }
}
