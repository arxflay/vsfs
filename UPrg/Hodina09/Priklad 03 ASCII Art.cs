// Tento zdrojovy kod jsem vypracoval zcela samostatne bez cizi pomoci
// Neokopiroval jsem ani neopsal jsem cizi zdrojove kody
// Nikdo mi pri vypracovani neradil
// Pokud nektery radek porusuje toto pravidlo je oznacen komentarem
// NENI MOJE TVORBA
// Poruseni techto pravidel se povazuje za podvod, ktery lze potrestat VYLOUCENIM ZE STUDIA
// Alexej Fedorenko, učo 37676 

using System;
namespace Priklad_03_ASCII_Art
{
    class Program
    {
        static void TestArt(char[,] matrix)
        {
            for (int i = 0; i < matrix.GetLength(0); i++)
            {
                for (int x = 0; x < matrix.GetLength(1); x++)
                    Console.Write(matrix[i, x]);
                Console.WriteLine();
            }
        }

        static char[,] Art00(int length) //a)
        {
            if (length <= 0 || length % 2 == 0)
                return null;
            
            char[,] matrix = new char[length, length];
            
            for (int i = 0; i < length; i++)
            {
                matrix[0, i] = '*';
                matrix[length - 1, i] = '*';
            }
            for (int i = 1; i < length - 1; i++)
            {
                matrix[i, 0] = '*';
                matrix[i, length - 1] = '*';
                for (int j = 1; j < length - 1; j++)
                    matrix[i, j] = ' ';
            }

            return matrix;
        }

        static char[,] Art01(int length) //b)
        {
            if (length <= 0 || length % 2 == 0)
                return null;
            
            char[,] matrix = new char[length, length];
            int mid = length / 2;

            for (int i = 0; i < length; i++)
            {
                matrix[0, i] = '*';
                matrix[length - 1, i] = '*';
            }
        
            for (int i = 1; i < length - 1; i++)
            {
                matrix[i, 0] = '*';
                matrix[i, length - 1] = '*';
                for (int j = 1; j < length - 1; j++)
                {
                    if (j == mid)
                        matrix[i, j] = '*';
                    else
                        matrix[i, j] = ' ';
                }
            }

            return matrix;
        }

        static char[,] Art02(int length) //c)
        {
            if (length <= 0 || length % 2 == 0)
                return null;
            
            char[,] matrix = new char[length, length];
            int shift = 1;

            for (int i = 0; i < length; i++)
            {
                matrix[0, i] = '*';
                matrix[length - 1, i] = '*';
            }
        
            for (int i = 1; i < length - 1; i++)
            {
                matrix[i, 0] = '*';
                matrix[i, length - 1] = '*';
                for (int j = 1; j < length - 1; j++)
                {
                    if (j == shift)
                        matrix[i, j] = '*';
                    else
                        matrix[i, j] = ' ';
                }
                shift++;
            }

            return matrix;
        }

        static char[,] Art03(int length) //d)
        {
            if (length <= 0 || length % 2 == 0)
                return null;
            
            char[,] matrix = new char[length, length];
            int shift = 1;

            for (int i = 0; i < length; i++)
            {
                matrix[0, i] = '*';
                matrix[length - 1, i] = '*';
            }
        
            for (int i = 1; i < length - 1; i++)
            {
                matrix[i, 0] = '*';
                matrix[i, length - 1] = '*';
                for (int j = 1; j < length - 1; j++)
                {
                    if (j == shift)
                    {
                        matrix[i, j] = '*';
                        matrix[i, (length - 1) - j] = '*';
                    }
                    else if (j != length - 1 - shift)
                        matrix[i, j] = ' ';
                }
                shift++;
            }

            return matrix;
        }

        static char[,] Art10(int length) //e)
        {
            if (length <= 0 || length % 2 == 0)
                return null;
            
            char[,] matrix = new char[length, length];
            int mid = length / 2;

            for (int i = 0; i < length; i++)
            {
                matrix[0, i] = '*';
                matrix[length - 1, i] = '*';
            }
        
            for (int i = 1; i < length - 1; i++)
            {
                matrix[i, 0] = '*';
                matrix[i, length - 1] = '*';
                for (int j = 1; j < length - 1; j++)
                {
                    if (i == mid || j == mid)
                        matrix[i, j] = '*';
                    else
                        matrix[i, j] = ' ';
                }
            }

            return matrix;
        }

        static char[,] Art11(int length) // f)
        {
            if (length <= 0 || length % 2 == 0)
                return null;
            
            char[,] matrix = new char[length, length];
            int mid = length / 2;
            int shift = 1;

            for (int i = 0; i < length; i++)
            {
                matrix[0, i] = '*';
                matrix[length - 1, i] = '*';
            }
        
            for (int i = 1; i < length - 1; i++)
            {
                matrix[i, 0] = '*';
                matrix[i, length - 1] = '*';
                for (int j = 1; j < length - 1; j++)
                {
                    if (i == mid || j == mid)
                        matrix[i, j] = '*';
                    else if (j == shift)
                    {
                        matrix[i, j] = '*';
                        matrix[i, (length - 1) - j] = '*';
                    }
                    else if (j != length - 1 - shift)
                        matrix[i, j] = ' ';
                }
                shift++;
            }

            return matrix;
        }

        static char[,] Art12(int length) // g)
        {
            if (length <= 0 || length % 2 == 0)
                return null;
            
            char[,] matrix = new char[length, length];
        
            for (int i = 0; i < length; i++)
            {
                matrix[i, 0] = '*';
                matrix[i, length - 1] = '*';
                for (int j = 1; j < length - 1; j++)
                {
                    if ((i + 2) % 2 == 0)
                        matrix[i, j] = '*';
                    else
                        matrix[i, j] = ' ';
                }
            }

            return matrix;
        }

        static char[,] Art13(int length) // h)
        {
            if (length <= 0 || length % 2 == 0)
                return null;
            
            char[,] matrix = new char[length, length];
        
            for (int i = 0; i < length; i++)
            {
                matrix[i, 0] = '*';
                matrix[i, length - 1] = '*';
                for (int j = 1; j < length - 1; j++)
                {
                    if ((i + 2) % 2 == 0)
                        matrix[i, j] = '*';
                    else if ((i + 2) % 2 == 1 && (j + 2) % 2 == 0)
                        matrix[i, j] = '*';
                    else
                        matrix[i, j] = ' ';
                }
            }

            return matrix;
        }

        static char[,] Art21(int length) // j)
        {
            if (length <= 0 || length % 2 == 0)
                return null;
            
            char[,] matrix = new char[length, length];
        
            for (int i = 0; i < length; i++)
            {
                for (int j = 0; j < length; j++)
                {
                    if (j < i)
                        matrix[i, j] = ' ';
                    else
                        matrix[i, j] = '*';
                }
            }

            return matrix;
        }

        static char[,] Art22(int length) // k)
        {
            if (length <= 0 || length % 2 == 0)
                return null;
            
            char[,] matrix = new char[length, length];

            int mid = length / 2;
        
            for (int i = 0; i < length; i++)
            {
                for (int j = 0; j < length; j++)
                {
                    if (j < i || j + i >= length)
                        matrix[i, j] = ' ';
                    else
                        matrix[i, j] = '*';
                }
            }

            return matrix;
        }

        static char[,] Art23(int length) // l)
        {
            if (length <= 0 || length % 2 == 0)
                return null;
            
            char[,] matrix = new char[length, length];

            int mid = length / 2;
        
            for (int i = 0; i < length; i++)
            {
                matrix[i, 0] = '*';
                matrix[i, length - 1] = '*';
                for (int j = 0; j < length; j++)
                {
                    if ((i > mid) && (i - mid + j >= mid) && (i >= j) || (i <= mid) && (j >= i) && (j <= length - 1 - i))
                        matrix[i, j] = '*';
                    else
                        matrix[i, j] = ' ';
                }
            }

            return matrix;
        }

        static char[,] Art30(int length) //m)
        {
            if (length <= 0 || length % 2 == 0)
                return null;
            
            char[,] matrix = new char[length, length];
            int mid = length / 2;

            for (int i = 0; i < length; i++)
            {
                matrix[0, i] = '*';
                matrix[length - 1, i] = '*';
            }

            for (int i = 1; i < length - 1; i++)
            {
                matrix[i, 0] = '*';
                matrix[i, length - 1] = '*';
                for (int j = 1; j < length - 1; j++)
                {
                    if (i == mid || j == mid)
                        matrix[i, j] = '*';
                    else
                        matrix[i, j] = ' ';
                }
            }
        
            for (int i = 1; i < mid; i++)
            {
                if (i % 2 == 0)
                {
                    for (int j = i; j <= mid - i; j++)
                    {   
                        //left top
                        matrix[i, j] = '*';  
                        matrix[j, i] = '*';
                        matrix[mid - i, j] = '*';
                        matrix[j, mid - i] = '*';

                        //right top
                        matrix[i, length - 1 - j] = '*';
                        matrix[j, length - 1 - i] = '*'; 
                        matrix[mid - i, length - 1 - j] = '*';
                        matrix[mid - j, mid + i] = '*';

                        //left bottom                      
                        matrix[mid + i, j] = '*';
                        matrix[mid + j, i] = '*';
                        matrix[length - 1 - i, j] = '*';
                        matrix[mid + j, mid - i] = '*';

                        //right bottom
                        matrix[mid + i, length - 1 - j] = '*';
                        matrix[mid + j, length - 1 - i] = '*';
                        matrix[length - 1 - i, mid + j] = '*';
                        matrix[mid + j, mid + i] = '*';                     
                    }
                }
            }

            return matrix;
        }

        static char[,] Art31(int length) //n)
        {
            if (length <= 0 || length % 2 == 0)
                return null;
            
            char[,] matrix = new char[length, length];
            int mid = length / 2;

            for (int i = 0; i < length; i++)
            {
                matrix[0, i] = '*';
                matrix[length - 1, i] = '*';
            }

            for (int i = 1; i < length - 1; i++)
            {
                matrix[i, 0] = '*';
                matrix[i, length - 1] = '*';
                for (int j = 1; j < length - 1; j++)
                {
                    if (i == mid || j == mid)
                        matrix[i, j] = '*';
                    else
                        matrix[i, j] = ' ';
                }
            }

            //top left
            for (int i = 1; i < mid; i++)
            {
                matrix[i,i] = '*';
                matrix[i,mid - i] = '*';
            }

            //top right
            for (int i = 1; i < mid; i++)
            {
                if (i % 2 == 0)
                    for (int j = 1; j < mid; j++)
                        matrix[j,mid + i] = '*';
            }

            //bottom left
            for (int i = 1; i < mid; i++)
            {
                for (int j = 1; j < mid; j++)
                {
                    if (i % 2 == 0)
                    {
                        matrix[mid + i,j] = '*';
                    }
                    else if (j % 2 == 0)
                        matrix[mid + i,j] = '*';
                }
            }
            
            //bottom right
            for (int i = 1; i < mid; i++)
            {
                if (i % 2 == 0)
                {
                    for (int j = i; j <= mid - i; j++)
                    {   
                        //left top
                        matrix[mid + i, length - 1 - j] = '*';
                        matrix[mid + j, length - 1 - i] = '*';
                        matrix[length - 1 - i, mid + j] = '*';
                        matrix[mid + j, mid + i] = '*';              
                    }
                }
            }

            return matrix;
        }

        static char[,] Art32(int length) //o)
        {
            if (length <= 0 || length % 2 == 0)
                return null;
            
            char[,] matrix = new char[length, length];
            int mid = length / 2;

            for (int i = 0; i < length; i++)
            {
                matrix[0, i] = '*';
                matrix[length - 1, i] = '*';
            }
        
            for (int i = 1; i < length - 1; i++)
            {
                matrix[i, 0] = '*';
                matrix[i, length - 1] = '*';
                for (int j = 1; j < length - 1; j++)
                {
                    if ((i == mid - 1 || i == mid + 1) && j != mid || ( j == mid - 1 || j == mid + 1) && i != mid)
                        matrix[i, j] = '*';
                    else
                        matrix[i, j] = ' ';
                }
            }

            return matrix;
        }

        static char[,] Art33(int length) //p)
        {
            if (length <= 0 || length % 2 == 0)
                return null;
            
            char[,] matrix = new char[length, length];
            int mid = length / 2;

            for (int i = 0; i < length; i++)
            {
                matrix[0, i] = '*';
                matrix[length - 1, i] = '*';
            }
        
            for (int i = 1; i < length - 1; i++)
            {
                matrix[i, 0] = '*';
                matrix[i, length - 1] = '*';
                for (int j = 1; j < length - 1; j++)
                {
                    if (i == mid || i == 1 || i == length - 2 || j == 1 || j == length - 2 || j == mid)
                        matrix[i, j] = ' ';
                    else
                        matrix[i, j] = '*';
                }
            }

            return matrix;
        }

        static void Main(string[] args)
        {           
            TestArt(Art31(25));
        }
    }
}
