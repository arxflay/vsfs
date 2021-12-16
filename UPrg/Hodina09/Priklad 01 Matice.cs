// Tento zdrojovy kod jsem vypracoval zcela samostatne bez cizi pomoci
// Neokopiroval jsem ani neopsal jsem cizi zdrojove kody
// Nikdo mi pri vypracovani neradil
// Pokud nektery radek porusuje toto pravidlo je oznacen komentarem
// NENI MOJE TVORBA
// Poruseni techto pravidel se povazuje za podvod, ktery lze potrestat VYLOUCENIM ZE STUDIA
// Alexej Fedorenko, učo 37676 
using System;
using System.IO;
namespace Priklad_01_Matice
{
    class Program
    {
        static long[,] CreateMatrix(int m, int n) //a)
        {
            if (m <= 0 || n <= 0)
                return null;

            long[,] matrix = new long[m,n];
            Random prnd = new Random();

            for (int i = 0; i < m; i++)
                for (int j = 0; j < n; j++)
                    matrix[i, j] = prnd.Next(-4, 5);

            return matrix;
        }

        static void SaveMatrix(long[,] matrix, string filename) //b)
        {
            if (matrix == null)
                return;

            StreamWriter sw = new StreamWriter(filename);
            int m = matrix.GetLength(0);
            int n = matrix.GetLength(1);
            sw.WriteLine("{0}x{1}", m, n);

            for (int i = 0; i < m; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    if (j != n - 1)
                        sw.Write("{0} ", matrix[i,j]);
                    else
                        sw.WriteLine(matrix[i,j]);
                }
            }     
            sw.Close();
        }

        static long[,] LoadMatrix(string filename) //c)
        {
            long[,] matrix = null;

            if (!File.Exists(filename))
                return matrix;

            StreamReader sr = new StreamReader(filename); 
            int m = 0;
            int n = 0;

            string size = sr.ReadLine();
            if (size == null)
                return matrix;

            string[] mn = size.Split('x');
            if (mn.Length != 2)
                return matrix;

            m = Convert.ToInt32(mn[0]);
            n = Convert.ToInt32(mn[1]);

            matrix = new long[m,n];

            string line = "";
            int row = 0;

            while((line = sr.ReadLine()) != null && row != m)
            {
                string[] numbers = line.Split(' ');

                if (numbers.Length != n)
                    break;

                for (int i = 0; i < n; i++)
                    matrix[row, i] = Convert.ToInt64(numbers[i]);

                row++;
            }
  
            sr.Close();
            return matrix;
        }
        
        static long[,] TranponseMatrix(long[,] matrix) //d)
        {
            if (matrix == null)
                return matrix;

            int m = 0;
            int n = 0;
            m = matrix.GetLength(0);
            n = matrix.GetLength(1);
            
            long[,] tranposedMatrix = new long[n,m];
            for (int i = 0; i < m; i++)
                for (int x = 0; x < n; x++)
                    tranposedMatrix[x,i] = matrix[i,x];

            return tranposedMatrix;
        }

        static bool IsMatrixSymmetric(long[,] matrix) //e)
        {
            if (matrix == null)
                return false;

            int m = matrix.GetLength(0);
            int n = matrix.GetLength(1);
            if (m != n)
                return false;

            for (int i = 1; i < m; i++)
            {
                for (int x = 0; x < 2; x++)
                {
                    int innerElementsCount = ((i + 1) / 2);

                    for (int j = 0; j < innerElementsCount; j++)
                        if (matrix[0 + j, i] != matrix[i, 0 + j])
                            return false;

                    if (i == m - 1)
                        break;
                    
                    for (int j = 0; j < innerElementsCount; j++)
                        if (matrix[m - 1 - i - j, m - 1] != matrix[m - 1, m - 1 - i - j])
                            return false;
                }
            }

            return true;
        }

        static long[] GetDiagonal (long[,] matrix) //e)
        {
            if (matrix == null)
                return null;

            int m = matrix.GetLength(0);
            int n = matrix.GetLength(1);
            int smallest = m;

            if (smallest > n)
                smallest = n;

            long[] diagonal = new long[smallest];
            for (int i = 0; i < smallest; i++)
                diagonal[i] = matrix[i,i];

            return diagonal;
        }

        static bool IsUpperTriangleMatrix (long[,] matrix) //e)
        {
            if (matrix == null)
                return false;

            int m = matrix.GetLength(0);
            int n = matrix.GetLength(1);
            if (m != n)
                return false;

            for (int i = 1; i < m; i++)
                for (int x = 0; x < i; x++)
                    if (matrix[i,x] != 0)
                        return false;

            return true;
        }
        
        static int CountZerosFromLeft(long[,] matrix, int row) //h)
        {
            if (matrix == null)
                return -1;

            int m = matrix.GetLength(0);
            if (row >= m || row < -1)
                return -1;

            int count = 0;
            for (int i = 0; i < matrix.GetLength(1); i++)
            {
                if (matrix[row, i] != 0)
                    break;
                count++;
            }

            return count;          
        }

        static bool IsStupnovanaMatice(long[,] matrix) //i)
        {
            if (matrix == null)
                return false;

            int zeroCount = -1;

            for (int i = 0; i < matrix.GetLength(0); i++)
            {
                int tempZeroCount = CountZerosFromLeft(matrix, i);
                if (zeroCount >= tempZeroCount)
                    return false;
                
                zeroCount = tempZeroCount;
            }

            return true;
        }

        static bool IsIdentityMatrix(long[,] matrix) //j)
        {
            long[] diagonal = GetDiagonal(matrix);

            if (diagonal == null)
                return false;

            for (int i = 0; i < diagonal.Length; i++)
                if (diagonal[i] != 1)
                    return false;

            return true;
        }

        static void Main(string[] args)
        {
            long[,] matrix = CreateMatrix(10,5);
            SaveMatrix(matrix, "matice1.txt");
            long[,] matrix2 = LoadMatrix("matice1.txt");
            long[,] matrix3 = { {2, 3, 1 }, { 7, 4, 6 } };
            long[,] matrix4 = TranponseMatrix(matrix3);
            long[,] matrix5 = { { 2, 6, 1 }, { 6, 4, 3 }, { 1, 3, 7 } };
            long[,] matrix6 = { { 2, 6, 3, 4, 9 }, { 6, 5, 8, 1, 4 }, { 3, 8, 0, 8, 3 }, { 4, 1, 8, 5, 6}, { 9, 4, 3, 6, 2 } };
            /*2 6 3 4 9
              6 5 8 1 4
              3 8 0 8 3
              4 1 8 5 6
              9 4 3 6 2
            */
            bool isMatrixSymmetric = IsMatrixSymmetric(matrix6);
            Console.WriteLine(isMatrixSymmetric);
            long[] v1 = GetDiagonal(matrix5);
            long[,] matrix7 = { { 4, 5, 2 }, { 0, 3, 6 }, { 0, 0 ,9 } };
            bool isUpperTriangleMatrix = IsUpperTriangleMatrix(matrix7);
            Console.WriteLine(isUpperTriangleMatrix);
            int i1 = CountZerosFromLeft(matrix7, 2);
            Console.WriteLine(i1);
            long[,] matrix8 = { { 7, 1, 2 }, { 0, 0, 6 } };
            bool isStupnovanaMatice = IsStupnovanaMatice(matrix8);
            Console.WriteLine(isStupnovanaMatice);
            bool isIdentityMatrix = IsIdentityMatrix(matrix7);
            Console.WriteLine(isIdentityMatrix);
        }
    }
}
