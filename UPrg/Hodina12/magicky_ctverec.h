// Tento zdrojovy kod jsem vypracoval zcela samostatne bez cizi pomoci
// Neokopiroval jsem ani neopsal jsem cizi zdrojove kody
// Nikdo mi pri vypracovani neradil
// Pokud nektery radek porusuje toto pravidlo je oznacen komentarem
// NENI MOJE TVORBA
// Poruseni techto pravidel se povazuje za podvod, ktery lze potrestat VYLOUCENIM ZE STUDIA
// Alexej Fedorenko, učo 37676 
#ifndef magicky_ctverec_h
#define magicky_ctverec_h
#include <stdbool.h>

typedef struct Sums
{
    int* row_sums;
    int* col_sums;
    int diagonal_left_sum;
    int diagonal_right_sum;
} Sums;

typedef struct Matrix
{
    int** data;
    int m_len;
    int n_len;
} Matrix;

Sums* Sums_create(int n);
void Sums_destroy(Sums* sums);

void increase_sum(Sums* sums, int row, int col, int num, bool is_diagonal_left, bool is_diagonal_right);
void decrease_sum(Sums* sums, int row, int col, int num, bool is_diagonal_left, bool is_diagonal_right);

Matrix* Matrix_create(int n, int m);
void Matrix_destroy(Matrix* matrix);

void magic_square(const char* filename, int n);

bool solve_row(Matrix* matrix, bool is_even, int magic_constant, Sums* sums, 
               bool* available_numbers, int n_square, int row, int col);
bool solve_col(Matrix* matrix, bool is_even, int magic_constant, Sums* sums, 
               bool* available_numbers, int n_square, int row, int col);

bool unreasonable_to_con(Sums* sums, int magic_constant, int row, 
                         int col, int num, bool is_diagonal_left, bool is_diagonal_right);
bool is_mid(int row, int col, int mid);

#endif