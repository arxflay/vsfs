using System;
// Tento zdrojovy kod jsem vypracoval zcela samostatne bez cizi pomoci
// Neokopiroval jsem ani neopsal jsem cizi zdrojove kody
// Nikdo mi pri vypracovani neradil
// Pokud nektery radek porusuje toto pravidlo je oznacen komentarem
// NENI MOJE TVORBA
// Poruseni techto pravidel se povazuje za podvod, ktery lze potrestat VYLOUCENIM ZE STUDIA
// Alexej Fedorenko, učo 37676 
namespace Priklad_06_Kamen__nuzky__papir
{
    class Program
    {
        enum Item
        {
            Kamen, Nuzky, Papir
        }

        static void Main(string[] args)
        {
            Random prnd = new Random();
            int computerWins = 0, playerWins = 0;
            Item pItem = Item.Kamen, cItem = Item.Kamen;
            string pInput = "";
            Console.WriteLine("Vitejte ve hre Kamen - Nuzky - Papir");
            Console.WriteLine("Hrajeme na dve vitezna kola");
            Console.WriteLine("Nazev predmetu musi zacinat velkym pismenem, Kamen | Nuzky | Papir");
            while (computerWins != 2 && playerWins != 2)
            {
                Console.Write("Zadejte svůj tah: ");
                pInput = Console.ReadLine();

                if (pInput != "Kamen" && pInput != "Papir" && pInput != "Nuzky")
                {
                    Console.WriteLine("Neplatny tah");
                    continue;
                }

                pItem = (Item)Enum.Parse(typeof(Item), pInput);
                cItem = (Item)prnd.Next(0, 3);

                Console.WriteLine("Hrac zahral {0}, pocitac zahral {1}", pItem.ToString(), cItem.ToString());
                switch(pItem)
                {
                    case Item.Kamen:
                        switch (cItem)
                        {
                            case Item.Kamen:
                                Console.WriteLine("Toto kolo je nerozhodne");
                                break;
                            case Item.Nuzky:
                                Console.WriteLine("Toto kolo vyhral hrac");
                                playerWins++;
                                break;
                            case Item.Papir:
                                Console.WriteLine("Toto kolo vyhral pocitac");
                                computerWins++;
                                break;
                        }
                        break;
                    case Item.Nuzky:
                        switch (cItem)
                        {
                            case Item.Kamen:
                                Console.WriteLine("Toto kolo vyhral pocitac");
                                computerWins++;
                                break;
                            case Item.Nuzky:
                                Console.WriteLine("Toto kolo je nerozhodne");
                                break;
                            case Item.Papir:
                                Console.WriteLine("Toto kolo vyhral hrac");
                                playerWins++;
                                break;
                        }
                        break;
                    case Item.Papir:
                        switch (cItem)
                        {
                            case Item.Kamen:
                                Console.WriteLine("Toto kolo vyhral hrac");
                                playerWins++;
                                break;
                            case Item.Nuzky:
                                Console.WriteLine("Toto kolo vyhral pocitac");
                                computerWins++;
                                break;
                            case Item.Papir:
                                Console.WriteLine("Toto kolo je nerozhodne");
                                break;
                        }
                        break;
                }
                Console.WriteLine("Celkove skore: hrac {0} - pocitac {1}", playerWins, computerWins);
            }
            if (computerWins > playerWins)
                Console.WriteLine("Celou hru vyhral pocitac");
            else
                Console.WriteLine("Celou hru vyhral hrac");
            Console.ReadKey();
        }
    }
}
