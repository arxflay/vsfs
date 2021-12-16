// Tento zdrojovy kod jsem vypracoval zcela samostatne bez cizi pomoci
// Neokopiroval jsem ani neopsal jsem cizi zdrojove kody
// Nikdo mi pri vypracovani neradil
// Pokud nektery radek porusuje toto pravidlo je oznacen komentarem
// NENI MOJE TVORBA
// Poruseni techto pravidel se povazuje za podvod, ktery lze potrestat VYLOUCENIM ZE STUDIA
// Alexej Fedorenko, učo 37676 
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <assert.h>
#include <string.h>

#include "magicky_ctverec.h"

Sums* Sums_create(int n)
{
    Sums* sums = (Sums*)calloc(1, sizeof(Sums));
    assert(sums != NULL && "Sums memory allocation error");

    sums->diagonal_left_sum = sums->diagonal_right_sum = 0;

    sums->row_sums = (int*)calloc(n, sizeof(int));
    assert(sums != NULL && "Sums rowSums memory allocation error");

    sums->col_sums = (int*)calloc(n, sizeof(int));
    assert(sums != NULL && "Sums rowSums memory allocation error");
    
    return sums;
}

void Sums_destroy(Sums* sums)
{
    if (sums)
    {
        if (sums->row_sums)
            free(sums->row_sums);
        if (sums->col_sums)
            free(sums->col_sums);

        free(sums);
    }
}

void increase_sum(Sums* sums, int row, int col, int num, bool is_diagonal_left, bool is_diagonal_right)
{
    sums->row_sums[row] += num;
    sums->col_sums[col] += num;

    if (is_diagonal_left)
        sums->diagonal_left_sum += num;

    if (is_diagonal_right)
        sums->diagonal_right_sum += num;
}

void decrease_sum(Sums* sums, int row, int col, int num, bool is_diagonal_left, bool is_diagonal_right)
{
    sums->row_sums[row] -= num;
    sums->col_sums[col] -= num;

    if (is_diagonal_left)
        sums->diagonal_left_sum -= num;

    if (is_diagonal_right)
        sums->diagonal_right_sum -= num;
}

Matrix* Matrix_create(int m, int n)
{
    Matrix* matrix = (Matrix*)calloc(1, sizeof(Matrix));
    assert(matrix != NULL && "matrix memory allocation error");

    matrix->m_len = m;
    matrix->n_len = n;

    matrix->data = (int**)calloc(m, sizeof(int*));
    assert(matrix->data != NULL && "Matrix row memory allocation error");

    for (int i = 0; i < m; i++)
    {
        matrix->data[i] = (int*)calloc(n, sizeof(int));
        assert(matrix->data[i] != NULL && "Matrix col memory allocation error");
    }

    return matrix;
}

void Matrix_destroy(Matrix* matrix)
{
    if (matrix)
    {
        if (matrix->data)
        {
            for (int i = 0; i < matrix->m_len; i++)
                if (matrix->data[i] != NULL)
                    free(matrix->data[i]);

            free(matrix->data);
        }
        free(matrix);
    }
}

void magic_square(const char* filename, const int n)
{
    if (n <= 2)
        return;

    FILE* file = fopen(filename, "w+");
    assert(file != NULL && "file creation/open error");

    Sums* sums = Sums_create(n);
    Matrix* matrix = Matrix_create(n, n);
    int n_square = n * n;
    int magic_constant = (int)(n * ((double)(n_square + 1) / 2));
    bool is_even = n % 2 == 0;
    bool* availableNumbers = (bool*)calloc(n_square, sizeof(bool));

    for (int i = 0; i < n_square; i++)
        availableNumbers[i] = true;

    solve_row(matrix, is_even, magic_constant, sums, availableNumbers, n_square, 0, 0);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (j == n - 1)
                fprintf(file, "%d\n", matrix->data[i][j]);
            else
                fprintf(file, "%d ", matrix->data[i][j]);
        }
    } 
    
    Sums_destroy(sums);
    Matrix_destroy(matrix);
    free(availableNumbers);
    fclose(file);
}

bool unreasonable_to_con(Sums* sums, int magic_constant, int row, 
                         int col, int num, bool is_diagonal_left, bool is_diagonal_right)
{
    return (sums->row_sums[row] + num > magic_constant)
        || (sums->col_sums[col] + num > magic_constant)
        || (is_diagonal_left && ((sums->diagonal_left_sum + num) > magic_constant))
        || (is_diagonal_right && ((sums->diagonal_right_sum + num) > magic_constant));
}

bool is_mid(int row, int col, int mid)
{
    return (row == mid && col == mid);
}

bool solve_row(Matrix* matrix, bool is_even, int magic_constant, Sums* sums, 
               bool* available_numbers, int n_square, int row, int col)
{
    int end = matrix->m_len - 1;
    int mid = matrix->m_len / 2;
    int num = 0;
    bool is_magic_square = false;
    bool is_diagonal_left = row == col;
    bool is_diagonal_right = col == (end - row);

    for (int i = 0; i < n_square; i++)
    {
        if (!available_numbers[i])
            continue;
        
        num = i + 1;

        if (unreasonable_to_con(sums, magic_constant, row, col, num, is_diagonal_left, is_diagonal_right))
            return false;
        else if (!is_even && is_mid(row, col, mid) && sums->diagonal_right_sum + num != magic_constant)
            continue;

        matrix->data[row][col] = num;
        available_numbers[i] = false;
        increase_sum(sums, row, col, num, is_diagonal_left, is_diagonal_right);

        if (col == end && sums->row_sums[row] == magic_constant)
        {
            if (row == end)
                is_magic_square = sums->diagonal_left_sum == magic_constant;
            else
                is_magic_square = solve_col(matrix, is_even, magic_constant, sums, available_numbers, n_square, row + 1, row);
        }
        else if (col != end)
            is_magic_square = solve_row(matrix, is_even, magic_constant, sums, available_numbers, n_square, row, col + 1);

        if (is_magic_square)
            return true;
        else
        {
            available_numbers[i] = true;
            decrease_sum(sums, row, col, num, is_diagonal_left, is_diagonal_right);
        }
    }
    return false;
}

bool solve_col(Matrix* matrix, bool is_even, int magic_constant, Sums* sums, 
               bool* available_numbers, int n_square, int row, int col)
{
    int end = matrix->m_len - 1;
    int mid = matrix->m_len / 2;
    int num = 0;
    bool is_magic_square = false;
    bool is_diagonal_left = row == col;
    bool is_diagonal_right = col == (end - row);

    for (int i = 0; i < n_square; i++)
    {
        if (!available_numbers[i])
            continue;
        
        num = i + 1;

        if (unreasonable_to_con(sums, magic_constant, row, col, num, is_diagonal_left, is_diagonal_right))
            return false;
        else if(is_even && col == mid - 1 && row == mid && sums->diagonal_right_sum + num != magic_constant)
            continue;
     
        matrix->data[row][col] = num;
        available_numbers[i] = false;
        increase_sum(sums, row, col, num, is_diagonal_left, is_diagonal_right);

        if (row == end && sums->col_sums[col] == magic_constant)
            is_magic_square = solve_row(matrix, is_even, magic_constant, sums, available_numbers, n_square, col + 1, col + 1);
        else if (row != end)
            is_magic_square = solve_col(matrix, is_even, magic_constant, sums, available_numbers, n_square, row + 1, col);


        if (is_magic_square)
            return true;
        else
        {
            available_numbers[i] = true;
            decrease_sum(sums, row, col, num, is_diagonal_left, is_diagonal_right);
        }
    }

    return false;
}

int main(void)
{
    time_t past = time(NULL);
    magic_square("magicky_ctverec.txt", 5);
    time_t elapsed = time(NULL) - past;
    printf("%lu:%lu:%lu \n", (elapsed / 3600) % 24, (elapsed / 60) % 60, elapsed % 60);
    return 0;
}
