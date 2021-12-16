// Tento zdrojovy kod jsem vypracoval zcela samostatne bez cizi pomoci
// Neokopiroval jsem ani neopsal jsem cizi zdrojove kody
// Nikdo mi pri vypracovani neradil
// Pokud nektery radek porusuje toto pravidlo je oznacen komentarem
// NENI MOJE TVORBA
// Poruseni techto pravidel se povazuje za podvod, ktery lze potrestat VYLOUCENIM ZE STUDIA
// Alexej Fedorenko, učo 37676 
using System;
using System.IO;

namespace Priklad_01_Rekurze_s_jednim_volanim
{
    class Program
    {
        private static int Min(int[] array) //a)
        {
            StreamWriter logWriter = new StreamWriter("log.txt", true);
            logWriter.WriteLine("Start Min(array)");

            int result = MinRec(array, 0, array.Length - 1, logWriter);

            logWriter.WriteLine("Konec Min(array) = {0}\n", result);
            logWriter.Close();

            return result;
        }

        private static int MinRec(int[] array, int start, int current, StreamWriter logWriter)
        {
            logWriter.WriteLine("Start MinRec(array, {0}, {1})", start, current);

            int result = 0;

            if (current == 0)
                result = array[current];
            else
                result = MinRec(array, 0, current - 1, logWriter);
                result = (array[current] < result) ? array[current] : result;

            logWriter.WriteLine("Konec MinRec(array, {0}, {1}) = {2}", start, current, result);

            return result;
        }

        private static int Sum(int[] array) //b
        {
            StreamWriter logWriter = new StreamWriter("log.txt", true);
            logWriter.WriteLine("Start Sum(array)");

            int result = SumRec(array, 0, array.Length - 1, logWriter);

            logWriter.WriteLine("Start Sum(array) = {0}\n", result);
            logWriter.Close();

            return result;
        }

        private static int SumRec(int[] array, int start, int current, StreamWriter logWriter)
        {
            int result = 0;

            if (array[current] < 0)
            {
                if (current == 0)
                    return 0;
                else
                {
                    result = SumRec(array, 0, current - 1, logWriter);
                    return result;
                }
            }

            logWriter.WriteLine("Start SumRec(array, {0}, {1})", start, current);

            if (current == 0)
                result = array[current];
            else
                result = array[current] + SumRec(array, 0, current - 1, logWriter);

            logWriter.WriteLine("Konec SumRec(array, {0}, {1}) = {2}", start, current, result);

            return result;
        }

        private static int Min2(int[] array) //c)
        {
            StreamWriter logWriter = new StreamWriter("log.txt", true);
            logWriter.WriteLine("Start Min2(array)");

            int result = Min2Rec(array, 0, array.Length - 1, logWriter);

            logWriter.WriteLine("Konec Min2(array) = {0}\n", result);
            logWriter.Close();

            return result;
        }

        private static int Min2Rec(int[] array, int start, int current, StreamWriter logWriter)
        {
            logWriter.WriteLine("Start Min2Rec(array, {0}, {1})", start, current);

            int result = 0;
            int result2 = 0;

            if (start < current)
            {
                int mid = (start + current) / 2;
                result = Min2Rec(array, start, mid, logWriter);
                result2 = Min2Rec(array, mid + 1, current, logWriter);
                result = (array[current] < result) ? array[current] : result;
                result = (result2 < result) ? result2 : result;
            }
            else
                result = array[current];

            logWriter.WriteLine("Konec Min2Rec(array, {0}, {1}) = {2}", start, current, result);

            return result;
        }

        private static int Sum2(int[] array) //d)
        {
            StreamWriter logWriter = new StreamWriter("log.txt", true);
            logWriter.WriteLine("Start Sum2(array)");

            int result = Sum2Rec(array, 0, array.Length - 1, logWriter);

            logWriter.WriteLine("Start Sum2(array) = {0}\n", result);
            logWriter.Close();

            return result;
        }

        private static int Sum2Rec(int[] array, int start, int current, StreamWriter logWriter)
        {
            int result = 0;
            int mid = (start + current) / 2;

            if (array[current] < 0)
            {
                if (start < current)
                {
                    result = Sum2Rec(array, start, mid, logWriter) + Sum2Rec(array, mid + 1, current, logWriter);
                    return result;
                }
                else
                    return 0;
            }

            logWriter.WriteLine("Start Sum2Rec(array, {0}, {1})", start, current);

            if (start < current)
                result = Sum2Rec(array, start, mid, logWriter) + Sum2Rec(array, mid + 1, current, logWriter);
            else
                result = array[current];

            logWriter.WriteLine("Konec Sum2Rec(array, {0}, {1}) = {2}", start, current, result);

            return result;
        }

        private static int Euklid(int divider, int divisor) //e)
        {
            if (divisor > divider)
            {
                int temp = divider;
                divider = divisor;
                divisor = temp;
            }  

            StreamWriter logWriter = new StreamWriter("log.txt", true);
            logWriter.WriteLine("Start Euklid({0}, {1})", divider, divisor);

            int result = EuklidRec(divider, divisor, logWriter);

            logWriter.WriteLine("Konec Euklid({0}, {1}) = {2}\n", divider, divisor, result);
            logWriter.Close();

            return result;
        }

        private static int EuklidRec(int divider, int divisor, StreamWriter logWriter)
        {
            int result = 0;

            logWriter.WriteLine("Start EuklidRec({0}, {1})", divider, divisor);

            if (divisor == 0)
                result = divider;
            else
            {
                int mod = divider % divisor;
                result = EuklidRec(divisor, mod, logWriter);
            }

            logWriter.WriteLine("Konec EuklidRec({0}, {1}) = {2}", divider, divisor, result);


            return result;
        }

        private static void Main(string[] args)
        {
            int[] array = { 7, 5, 6, -3, -2, 8, -5 };
            int min = Min(array);
            int sum = Sum(array);
            int min2 = Min2(array);
            int sum2 = Sum2(array);
            int euklid = Euklid(21,77);

            Console.WriteLine("min={0}\nsum={1}\nmin2={2}\nsum2={3}\neuklid={4}", min, sum, min2, sum2, euklid);
            Console.ReadKey();
        }
    }
}
