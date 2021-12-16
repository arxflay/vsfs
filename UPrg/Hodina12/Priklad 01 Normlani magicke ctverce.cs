// Tento zdrojovy kod jsem vypracoval zcela samostatne bez cizi pomoci
// Neokopiroval jsem ani neopsal jsem cizi zdrojove kody
// Nikdo mi pri vypracovani neradil
// Pokud nektery radek porusuje toto pravidlo je oznacen komentarem
// NENI MOJE TVORBA
// Poruseni techto pravidel se povazuje za podvod, ktery lze potrestat VYLOUCENIM ZE STUDIA
// Alexej Fedorenko, učo 37676 
using System;
using System.IO;
using System.Diagnostics;

namespace Priklad_01_Normalni_magicke_ctverce
{
    class Program
    {
        private struct Sums
        {
            public int[] rowSums;
            public int[] columnSums;
            public int diagonalLeftSum;
            public int diagonalRightSum;
        }

        private static Sums MagicSquareSumsCreate(int n)
        {
            Sums sums;
            sums.diagonalLeftSum = sums.diagonalRightSum = 0;
            sums.columnSums = new int[n];
            sums.rowSums = new int[n];

            return sums;
        }

        private static void IncreaseSum(ref Sums sums, int row, int col, int num, bool isDiagonalLeft, bool isDiagonalRight)
        {
            sums.rowSums[row] += num;
            sums.columnSums[col] += num;

            if (isDiagonalLeft)
                sums.diagonalLeftSum += num;

            if (isDiagonalRight)
                sums.diagonalRightSum += num;
        }

        private static void DecreaseSum(ref Sums sums, int row, int col, int num, bool isDiagonalLeft, bool isDiagonalRight)
        {
            sums.rowSums[row] -= num;
            sums.columnSums[col] -= num;

            if (isDiagonalLeft)
                sums.diagonalLeftSum -= num;

            if (isDiagonalRight)
                sums.diagonalRightSum -= num;
        }
         
        private static void MagicSquare(string filename, int n)
        {
            if (n <= 2)
                return;
            
            StreamWriter sw = new StreamWriter(filename);
            Sums sums = MagicSquareSumsCreate(n);
            int nSquare = n * n;
            int magicConstant = (int)(n * ((double)(nSquare + 1) / 2));
            bool isEven = n % 2 == 0;
            int[,] matrix = new int[n, n];
            bool[] availableNumbers = new bool[nSquare];

            for (int i = 0; i < availableNumbers.Length; i++)
                availableNumbers[i] = true;

            bool success = SolveRow(matrix, isEven, magicConstant, ref sums, availableNumbers, 0, 0);

            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    if (j == n - 1)
                        sw.WriteLine(matrix[i,j]);
                    else
                        sw.Write("{0} ", matrix[i,j]);

                }
            }
            
            sw.Close();
        }

        private static bool IsUnreasonableToContinue(Sums sums, int magicConstant, int row, 
                                            int col, int num, bool isDiagonalLeft, bool isDiagonalRight)
        {
            return (sums.rowSums[row] + num) > magicConstant 
                || (sums.columnSums[col] + num) > magicConstant 
                || (isDiagonalLeft && ((sums.diagonalLeftSum + num) > magicConstant))
                || (isDiagonalRight && ((sums.diagonalRightSum + num) > magicConstant));
        }

        private static bool IsMid(int row, int col, int mid)
        {
            return (row == mid && col == mid);
        }

        private static bool SolveRow(int[,] matrix, bool isEven, int magicConstant, ref Sums sums,
                                bool[] availableNumbers, int row, int col)
        {
            int end = matrix.GetLength(0) - 1;
            int mid = matrix.GetLength(0) / 2;
            int num = 0;
            bool isMagicSquare = false;
            bool isDiagonalLeft = row == col;
            bool isDiagonalRight = col == (end - row);

            for (int i = 0; i < availableNumbers.Length; i++)
            {
                if (!availableNumbers[i])
                    continue;
                
                num = i + 1;

                if (IsUnreasonableToContinue(sums, magicConstant, row, col, num, isDiagonalLeft, isDiagonalRight))
                    return false;
                else if (!isEven && IsMid(row, col, mid) && (sums.diagonalRightSum + num != magicConstant))
                    continue;
                
                matrix[row, col] = num;
                availableNumbers[i] = false;
                IncreaseSum(ref sums, row, col, num, isDiagonalLeft, isDiagonalRight);

                if (col == end && sums.rowSums[row] == magicConstant)
                {
                    if (row == end)
                        isMagicSquare = sums.diagonalLeftSum == magicConstant;
                    else
                        isMagicSquare = SolveColumn(matrix, isEven, magicConstant, ref sums, availableNumbers, row + 1, row);
                }
                else if (col != end)
                    isMagicSquare = SolveRow(matrix, isEven, magicConstant, ref sums, availableNumbers, row, col + 1);

                if (isMagicSquare)
                    return true;
                else
                {
                    availableNumbers[i] = true;
                    DecreaseSum(ref sums, row, col, num, isDiagonalLeft, isDiagonalRight);               
                }


            }
            return false;
        }

        private static bool SolveColumn(int[,] matrix, bool isEven, int magicConstant, ref Sums sums,
                                bool[] availableNumbers, int row, int col)
        {
            int end = matrix.GetLength(0) - 1;
            int mid = matrix.GetLength(0) / 2;
            int num = 0;
            bool isMagicSquare = false;
            bool isDiagonalLeft = row == col;
            bool isDiagonalRight = col == (end - row);

            for (int i = 0; i < availableNumbers.Length; i++)
            {
                if (!availableNumbers[i])
                    continue;
                
                num = i + 1;

                if (IsUnreasonableToContinue(sums, magicConstant, row, col, num, isDiagonalLeft, isDiagonalRight))
                    return false;
                else if (isEven && (col == mid - 1) && row == mid && (sums.diagonalRightSum + num != magicConstant))
                    continue;

                matrix[row, col] = num;
                availableNumbers[i] = false;
                IncreaseSum(ref sums, row, col, num, isDiagonalLeft, isDiagonalRight);

                if (row == end && sums.columnSums[col] == magicConstant)
                    isMagicSquare = SolveRow(matrix, isEven, magicConstant, ref sums, availableNumbers, col + 1, col + 1);
                else if (row != end)
                    isMagicSquare = SolveColumn(matrix, isEven, magicConstant, ref sums, availableNumbers, row + 1, col);

                if (isMagicSquare)
                    return true;
                else
                {
                    availableNumbers[i] = true;
                    DecreaseSum(ref sums, row, col, num, isDiagonalLeft, isDiagonalRight);               
                }
            }

            return false;
        }
   
        static void Main(string[] args)
        { 
            Stopwatch timer = new Stopwatch();
            timer.Start();
            MagicSquare("MagickyCtverec.txt", 7);
            timer.Stop();
            Console.WriteLine(timer.ElapsedMilliseconds);
        }
    }
}
