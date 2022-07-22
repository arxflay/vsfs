// Tento zdrojovy kod jsem vypracoval zcela samostatne bez cizi pomoci
// Neokopiroval jsem ani neopsal jsem cizi zdrojove kody
// Nikdo mi pri vypracovani neradil
// Pokud nektery radek porusuje toto pravidlo je oznacen komentarem
// NENI MOJE TVORBA
// Poruseni techto pravidel se povazuje za podvod, ktery lze potrestat VYLOUCENIM ZE STUDIA
// Alexej Fedorenko, učo 37676 

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void matDestroy(int **mat, size_t n)
{
    if (mat)
        for (size_t x = 0; x < n; x++)
            free(mat[x]);

    free(mat);
}

int **matCreate(size_t n, size_t m) //1)
{
    int **mat = (int**)malloc(sizeof(int*) * n);
    if (!mat)
        return NULL;

    for (size_t x = 0; x < n; x++)
    {
        mat[x] = (int*)calloc(m, sizeof(int));
        if (!mat[x])
        {
            matDestroy(mat, x);
            return NULL;
        }
    }

    return mat;
}

int nsd(int a, int b) //2)
{
    if (b == 0)
        return a;
    
    return nsd(b, a % b);
}

int nsn(int a, int b)
{
    return (a * b) / nsd(a, b);
}


typedef int (*mat_callback)(int, int);

void matForeach(int **mat, size_t n, size_t m, mat_callback cb) //3)
{
    if (!mat)
        return;

    for (size_t x = 0; x < n; x++)
        for (size_t y = 0; y < m; y++)
            mat[x][y] = cb(x + 1, y + 1);
            
}

void writeMat(int **mat, size_t n, size_t m, FILE *file)
{
    for (size_t x = 0; x < n; x++)
    {
        for (size_t y = 0; y < m; y++)
        {
            if (y + 1 == m)
                fprintf(file, "%d", mat[x][y]);
            else
                fprintf(file, "%d ", mat[x][y]);
        }
        
        if (x + 1 != n || file == stdout)
            fputc('\n', file);
    }
}

int main(int argc, char *argv[])
{
    mat_callback mat_cb = NULL;
    FILE *file = NULL;

    if (argc < 3)
    {
        fputs("valid usage: {-nsn | -nsd } [-f output] n [m]\n", stdout);
        return -1;
    }
    
    if (strcmp(argv[1], "-nsn") == 0) //4)
        mat_cb = nsn;
    else if (strcmp(argv[1], "-nsd") == 0)
        mat_cb = nsd;
    else
    {
        fputs("valid usage: {-nsn | -nsd } [-f output] n [m]\n", stdout);
        return -1;
    }

    int currentArg = 2;

    if (strcmp(argv[2], "-f") == 0)
    {
        if (argc < 5)
        {
            fputs("valid usage: {-nsn | -nsd } [-f output] n [m]\n", stdout);
            return -1;
        }

        file = fopen(argv[3], "w");
        if (!file)
        {
            fputs("Failed to open file to write\n", stdout);
            return -1;
        }

        currentArg = 4;
    }

    size_t n;
    if (sscanf(argv[currentArg], "%lu", &n) == 0)
    {
        if (file)
            fclose(file);
        fputs("invalid number\n", stdout);
        fputs("valid usage: {-nsn | -nsd } [-f output] n [m]\n", stdout);
        return -1;
    }
    currentArg++;

    size_t m = n;
    if (currentArg != argc && sscanf(argv[currentArg], "%lu", &m) == 0)
    {
        if (file)
            fclose(file);
        fputs("invalid number\n", stdout);
        fputs("valid usage: {-nsn | -nsd } [-f output] n [m]\n", stdout);
        return -1;
    }

    int **mat = matCreate(n, m);
    if (mat == NULL)
    {
        if (file)
            fclose(file);
        fputs("Failed to allocate memory for matrix \n", stdout);
        return -1;
    }

    matForeach(mat, n, m, mat_cb);

    if (file) //6)
    {
        writeMat(mat, n, m, file);
        fclose(file);
    }
    else //5)
        writeMat(mat, n, m, stdout);

    matDestroy(mat, n);

    return 0;
}