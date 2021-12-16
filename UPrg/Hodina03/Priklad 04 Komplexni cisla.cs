using System;
// Tento zdrojovy kod jsem vypracoval zcela samostatne bez cizi pomoci
// Neokopiroval jsem ani neopsal jsem cizi zdrojove kody
// Nikdo mi pri vypracovani neradil
// Pokud nektery radek porusuje toto pravidlo je oznacen komentarem
// NENI MOJE TVORBA
// Poruseni techto pravidel se povazuje za podvod, ktery lze potrestat VYLOUCENIM ZE STUDIA
// Alexej Fedorenko, učo 37676 
namespace Priklad_04_Komplexni_cisla
{
    class Program
    {
        struct ComplexNumber
        {
            public double re;
            public double im;
        }

        static ComplexNumber Sum(ComplexNumber x, ComplexNumber y) //a)
        {
            ComplexNumber result;
            result.re = x.re + y.re;
            result.im = x.im + y.im;

            return result;
        }

        static ComplexNumber Minus(ComplexNumber x, ComplexNumber y) //b)
        {
            ComplexNumber result;
            result.re = x.re - y.re;
            result.im = x.im - y.im;

            return result;
        }
        static ComplexNumber Multiply(ComplexNumber x, ComplexNumber y) //c)
        {
            ComplexNumber result;
            result.re = x.re * y.re - x.im * y.im;
            result.im = x.re * y.im + x.im * y.re;

            return result;
        }


        static void Main(string[] args)
        {
            ComplexNumber x, y, a, b, c;
            x.re = 5.2; 
            x.im = 3.25;
            y.re = 1.6;
            y.im = -4;

            a = Sum(x, y);
            b = Minus(x, y);
            c = Multiply(x, y);

            Console.WriteLine("{0} + ({1}i) {2} + ({3}i) {4} + ({5}i)", a.re, a.im, b.re, b.im, c.re, c.im);
            Console.ReadKey();
        }
    }
}
