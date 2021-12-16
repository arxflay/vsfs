using System;
// Tento zdrojovy kod jsem vypracoval zcela samostatne bez cizi pomoci
// Neokopiroval jsem ani neopsal jsem cizi zdrojove kody
// Nikdo mi pri vypracovani neradil
// Pokud nektery radek porusuje toto pravidlo je oznacen komentarem
// NENI MOJE TVORBA
// Poruseni techto pravidel se povazuje za podvod, ktery lze potrestat VYLOUCENIM ZE STUDIA
// Alexej Fedorenko, učo 37676 
namespace Priklad_02_BMI
{
    class Program
    {
        enum BMI
        {
            TezkaPodvyziva, Podvaha, OptimalniVaha, Nadvaha, ObezitaPrvnihoStupne, ObezitaDruhehoStupne, ObezitaTretihoStupne
        }

        static double CalculateBMI1(double heightInMeters, double weightInKilograms)
        {
            return weightInKilograms / (heightInMeters * heightInMeters);
        }

        static BMI CalculateBMI2(double heightInMeters, double weightInKilograms)
        {
            double bmi = CalculateBMI1(heightInMeters, weightInKilograms);
            if (bmi < 16.5)
                return BMI.TezkaPodvyziva;
            else if (bmi < 18.5)
                return BMI.Podvaha;
            else if (bmi < 25)
                return BMI.OptimalniVaha;
            else if (bmi < 30)
                return BMI.Nadvaha;
            else if (bmi < 35)
                return BMI.ObezitaPrvnihoStupne;
            else if (bmi < 40)
                return BMI.ObezitaDruhehoStupne;

            return BMI.ObezitaTretihoStupne;
        }

        static void Main(string[] args)
        {
            double x = CalculateBMI1(1.70, 61.5);
            BMI y = CalculateBMI2(1.67, 80);
            Console.WriteLine("BMI 1.70m, 61.5kg = {0:N2}", x);
            Console.WriteLine("BMI 1.67m, 80kg = {0}", y);
            Console.ReadKey();
        }
    }
}
