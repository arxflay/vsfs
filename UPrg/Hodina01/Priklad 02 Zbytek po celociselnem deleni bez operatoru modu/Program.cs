using System;
// Tento zdrojovy kod jsem vypracoval zcela samostatne bez cizi pomoci
// Neokopiroval jsem ani neopsal jsem cizi zdrojove kody
// Nikdo mi pri vypracovani neradil
// Pokud nektery radek porusuje toto pravidlo je oznacen komentarem
// NENI MOJE TVORBA
// Poruseni techto pravidel se povazuje za podvod, ktery lze potrestat VYLOUCENIM ZE STUDIA
// Alexej Fedorenko, učo 37676 
namespace Priklad_01_Zbytek_po_celociselnem_deleni_bez_operatoru_modul
{
    class Program
    {
        static void Main(string[] args)
        {
            int num = 10, divider = 4;
            int result = num - ((num/divider) * divider);

            Console.WriteLine("Zbytek po celociselnem deleni {0} cislem {1}: {2}", num, divider, result);
            Console.ReadKey();
        }
    }
}
