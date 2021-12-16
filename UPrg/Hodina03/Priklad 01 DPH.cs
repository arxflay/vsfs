using System;
// Tento zdrojovy kod jsem vypracoval zcela samostatne bez cizi pomoci
// Neokopiroval jsem ani neopsal jsem cizi zdrojove kody
// Nikdo mi pri vypracovani neradil
// Pokud nektery radek porusuje toto pravidlo je oznacen komentarem
// NENI MOJE TVORBA
// Poruseni techto pravidel se povazuje za podvod, ktery lze potrestat VYLOUCENIM ZE STUDIA
// Alexej Fedorenko, učo 37676 
namespace Priklad_01_DPH
{
    class Program
    {       
        enum DPH
        {
            Zakladni = 21, PrvniSnizena = 15, DruhaSnizena = 10
        }

        static double CalculateDPH1(double price, int taxPercentage)
        {
            return price + ((price / 100) * taxPercentage);
        }

        static double CalculateDPH2(double price, DPH tax)
        {
            return CalculateDPH1(price, (int)tax);
        }

        static void Main(string[] args)
        {
            double x = CalculateDPH1(56.20, 21);
            double y = CalculateDPH2(115, DPH.PrvniSnizena);
            Console.WriteLine("21% DPH z 56.20 = {0}", x);
            Console.WriteLine("15% DPH z 115   = {0}", y);
            Console.ReadKey();
        }
    }
}
