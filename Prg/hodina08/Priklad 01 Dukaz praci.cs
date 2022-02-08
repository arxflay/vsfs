// Tento zdrojovy kod jsem vypracoval zcela samostatne bez cizi pomoci
// Neokopiroval jsem ani neopsal jsem cizi zdrojove kody
// Nikdo mi pri vypracovani neradil
// Pokud nektery radek porusuje toto pravidlo je oznacen komentarem
// NENI MOJE TVORBA
// Poruseni techto pravidel se povazuje za podvod, ktery lze potrestat VYLOUCENIM ZE STUDIA
// Alexej Fedorenko, učo 37676 

using System;
using System.Security.Cryptography;
using System.Diagnostics;

//little endian implementation
namespace Priklad_01_Dukaz_praci
{
    class Program
    {
        static int getCurrentByte(int bitPos)
        {
            return bitPos / 8;
        }
        
        static int getCurrentBit(int bitPos, int currentByte)
        {
            return 1 << 7 - (bitPos - (8 * currentByte));
        }

        static bool isBitEqualsZero(byte[] hash, int bitPos)
        {
            int currentByte = getCurrentByte(bitPos);
            int bit = getCurrentBit(bitPos, currentByte);
            return (hash[currentByte] & bit) == 0;
        }

        const int COUNT_MAX = 256;

        //bit zeroes
        static int Mining(int expectedZeroBits)
        {
            if (expectedZeroBits > COUNT_MAX || expectedZeroBits < 0)
                throw new Exception("expected bit count must be less than 257 and heighier than 0");
    
            SHA256 cypher = SHA256.Create();
            int nonce = int.MinValue;
            bool found = false;

            while(!found)
            {
                found = true;
                byte[] bytes = BitConverter.GetBytes(nonce);
                cypher.ComputeHash(bytes);
                byte[] hash = cypher.Hash;
            
                for (int i = 0; i < expectedZeroBits; i++)
                {
                    if (!isBitEqualsZero(hash, i))
                    {
                        found = false;
                        nonce++;
                        break;
                    }
                }

                if (found && expectedZeroBits != COUNT_MAX && isBitEqualsZero(hash, expectedZeroBits))
                {
                    found = false;
                    nonce++;
                }
                
            }

            Console.WriteLine(Convert.ToHexString(cypher.Hash));

            return nonce;
        }

        //bit zeroes
        static void Test(int maxBitCount)
        {
            if (maxBitCount > COUNT_MAX || maxBitCount < 0)
                throw new Exception("expected count must be less than 256 and heighier than 0");

            Stopwatch sw = new Stopwatch();
            for (int i = 0; i <= maxBitCount; i++)
            {
                sw.Start();
                Mining(i);
                sw.Stop();
                Console.WriteLine("Pocet bit nul: {0}, cas: {1}ms", i, sw.ElapsedMilliseconds);
                sw.Reset();
            }
        }

        //hex zeroes
        static int Mining2(int expectedZeros)
        {
            if (expectedZeros > 64 || expectedZeros < 0)
                throw new Exception("expected byte count must be less than 65 and heighier than 0");

            return Mining(expectedZeros * 4);
        }

        //hex zeroes
        static void Test2(int maxZeroCount)
        {
            if (maxZeroCount > 65 || maxZeroCount < 0)
                throw new Exception("expected zero count must be less than 65 and heighier than 0");
            
            Stopwatch sw = new Stopwatch();

            for (int i = 0; i <= maxZeroCount; i++)
            {
                sw.Start();
                Mining2(i);
                sw.Stop();
                Console.WriteLine("Pocet nul: {0}, cas: {1}ms", i, sw.ElapsedMilliseconds);
                sw.Reset();
            }
        }

        static void Main(string[] args)
        {
            int nonce = Mining2(1);
            Console.WriteLine(nonce);
            Test2(4);
        }
    }
}
