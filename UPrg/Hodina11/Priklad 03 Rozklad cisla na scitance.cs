// Tento zdrojovy kod jsem vypracoval zcela samostatne bez cizi pomoci
// Neokopiroval jsem ani neopsal jsem cizi zdrojove kody
// Nikdo mi pri vypracovani neradil
// Pokud nektery radek porusuje toto pravidlo je oznacen komentarem
// NENI MOJE TVORBA
// Poruseni techto pravidel se povazuje za podvod, ktery lze potrestat VYLOUCENIM ZE STUDIA
// Alexej Fedorenko, učo 37676 
using System;
using System.IO;

namespace Priklad_03_Rozklad_cisla_na_scitance
{
    class Program
    {
        private struct Stack
        {
            public int[] elements;
            public int count;
        }

        private static Stack Create(int len)
        {
            Stack stack;

            stack.count = 0;
            stack.elements = new int[len];

            return stack;
        }
        
        private static void Push(ref Stack stack, int el) 
        {
            stack.elements[stack.count++] = el;
        }
        
        private static int Pop(ref Stack stack)
        {
            return stack.elements[--stack.count];
        }

        private static int Get(Stack stack, int i)
        {
            return stack.elements[i];
        }

        private static void WriteDecomposition(StreamWriter sw, Stack decomposition)
        {
            for (int i = 0; i < decomposition.count; i++)
            {
                if (i == decomposition.count - 1)
                    sw.WriteLine(decomposition.elements[i]);
                else
                    sw.Write("{0} ", decomposition.elements[i]);
            }
        }

        private static void Decomposition(string filename, int n)
        {
            StreamWriter sw = new StreamWriter(filename);
            Stack decomposition = Create(n);

            DecompositionRec(sw, ref decomposition, n, n, 0);

            sw.Close();
        }

        private static void DecompositionRec(StreamWriter sw, ref Stack decomposition, int n, int max, int sum)
        {
            for (int i = 1; i <= max; i++)
            {
                int sumRec = sum + i;
                if (sumRec > n)
                    break;

                Push(ref decomposition, i);

                if (sumRec < n)
                    DecompositionRec(sw, ref decomposition, n, i, sumRec);
                else if (sumRec == n)
                    WriteDecomposition(sw, decomposition);
                
                Pop(ref decomposition);           
            }
        }

        
        private static void Main(string[] args)
        {
            Decomposition("rozklad.txt", 6);
        }
    }
}
