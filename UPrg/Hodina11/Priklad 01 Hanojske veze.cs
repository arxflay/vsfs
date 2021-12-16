// Tento zdrojovy kod jsem vypracoval zcela samostatne bez cizi pomoci
// Neokopiroval jsem ani neopsal jsem cizi zdrojove kody
// Nikdo mi pri vypracovani neradil
// Pokud nektery radek porusuje toto pravidlo je oznacen komentarem
// NENI MOJE TVORBA
// Poruseni techto pravidel se povazuje za podvod, ktery lze potrestat VYLOUCENIM ZE STUDIA
// Alexej Fedorenko, učo 37676 
using System.IO;

namespace Priklad_01_Hanojske_veze
{
    class Program
    {
        private struct Stack
        {
            public int[] elements;
            public int count;
            public string name;
        }

        private static Stack Create(int len, string name)
        {
            Stack stack;

            stack.count = 0;
            stack.elements = new int[len];
            stack.name = name;

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

        private static int Peek(Stack stack)
        {
            return Get(stack, stack.count - 1);
        }

        private static bool IsEmpty(Stack stack)
        {
            return stack.count == 0;
        }

        private static void WriteTower(StreamWriter hanoiWriter, Stack tower)
        {
            hanoiWriter.Write("{0}: ", tower.name);

            if (IsEmpty(tower))
                hanoiWriter.WriteLine("nic");
            else
            {
                for (int i = 0; i < tower.count; i++)
                { 
                    if (i == tower.count - 1)
                        hanoiWriter.WriteLine(Get(tower, i));
                    else
                        hanoiWriter.Write("{0} ", Get(tower, i));
                }
            }
        }

        private static void HanoiTower(string filename, int n)
        {
            StreamWriter hanoiWriter = new StreamWriter(filename);
            Stack fromTower = Create(n, "Vez " + 1);
            Stack auxTower  = Create(n, "Vez " + 2);
            Stack toTower   = Create(n, "Vez " + 3);
    
            for (int i = n; i >= 1; i--)
                Push(ref fromTower, i);

            HanoiRec(n, ref fromTower, ref auxTower, ref toTower, hanoiWriter);
            
            hanoiWriter.WriteLine("Cilova vez: ");
            WriteTower(hanoiWriter, toTower);

            hanoiWriter.Close();
        }

        private static void HanoiRec(int n, ref Stack fromTower, ref Stack auxTower, ref Stack toTower, StreamWriter hanoiWriter)
        {
            if (n == 0)
                return;

            HanoiRec(n - 1, ref fromTower, ref toTower, ref auxTower, hanoiWriter);
            HanoiTah(hanoiWriter, ref fromTower, ref toTower);
            HanoiRec(n - 1, ref auxTower, ref fromTower, ref toTower, hanoiWriter);
        }

        private static void HanoiTah(StreamWriter hanoiWriter, ref Stack fromTower, ref Stack toTower)
        {
            int fromRod = -1;

            hanoiWriter.WriteLine("Pokusime se prenest disk z {0} na {1}", fromTower.name, toTower.name);

            WriteTower(hanoiWriter, fromTower);
            WriteTower(hanoiWriter, toTower);
         
            if (IsEmpty(fromTower))
            {
                hanoiWriter.WriteLine("Na zdrojove vezi se nenachazi zadny disk, nelze pokracovat v tahu\n");
                return;
            }

            fromRod = Peek(fromTower);
            hanoiWriter.WriteLine("Na zdrojove vezi se nachazi disk {0}, lze pokracovat v tahu.", fromRod);

            if (IsEmpty(toTower))
                hanoiWriter.WriteLine("Cilova vez je prazdna, lze provest tah");
            else
            {
                int toRod = Peek(toTower);

                hanoiWriter.WriteLine("Na cilove vezi se nachazi disk {0}", toRod);          
                if (fromRod > toRod)
                {
                    hanoiWriter.WriteLine("Nelze polozit vetsi disk {0} na mensi disk {1}\n", fromRod, toRod);
                    return;
                }
                else
                    hanoiWriter.WriteLine("Lze polozit mensi disk {0} na vetsi disk {1}", fromRod, toRod);
            }
            
            hanoiWriter.WriteLine("Presouvame disk {0} z {1} na {2}\n", fromRod, fromTower.name, toTower.name);
            Push(ref toTower, Pop(ref fromTower));
        }

        private static void Main(string[] args)
        {
            HanoiTower("hanoi.txt", 4);
        }
    }
}
