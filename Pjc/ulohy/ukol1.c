// Tento zdrojovy kod jsem vypracoval zcela samostatne bez cizi pomoci
// Neokopiroval jsem ani neopsal jsem cizi zdrojove kody
// Nikdo mi pri vypracovani neradil
// Pokud nektery radek porusuje toto pravidlo je oznacen komentarem
// NENI MOJE TVORBA
// Poruseni techto pravidel se povazuje za podvod, ktery lze potrestat VYLOUCENIM ZE STUDIA
// Alexej Fedorenko, učo 37676 

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

void clear_stdbuffer()
{
    for(char c = fgetc(stdin); c != '\n' && c != EOF; c = fgetc(stdin));
}

int getDigit(const char *enterText, const char *errorText)
{
    int a = 0;
    int err = 0;

    while(true)
    {
        fputs(enterText, stdout);
        err = scanf("%1d", &a);

        clear_stdbuffer();
        if (err == 0)
        {
            printf(errorText, stdout);
            continue;
        }

        break;
    }

    return a;
}

bool isArithmeticOp(const char *op)
{
    return strcmp(op, "+")  == 0 
        || strcmp(op, "-")  == 0 
        || strcmp(op, "/")  == 0  
        || strcmp(op, "*")  == 0;
}

void strToLower(char *buffer, size_t n)
{
    for (size_t i = 0; i < n; i++)
        buffer[i] = tolower(buffer[i]);
}

int main(void)
{
    double memory = 0;
    int b = 0;
    bool cleared = true;
    char buffer[5];

    while(true)
    {
        memset(buffer, 0, sizeof(buffer));

        if (cleared)
        {
            memory = getDigit("Zadejde cislo 1: ", "\nNezadal jste cislo, zkuste znovu\n");
            cleared = false;
        }

        fputs("Zadejde operaci: ", stdout);
        scanf("%4s", buffer);
        strToLower(buffer, strlen(buffer));
        clear_stdbuffer();
        
        if (strcmp(buffer, "q") == 0)
            break;
        else if (strcmp(buffer, "sin") == 0)
            memory = sin(memory);
        else if (strcmp(buffer, "cos") == 0)
            memory = cos(memory);
        else if (strcmp(buffer, "x^2") == 0)
            memory = pow(memory, 2);
        else if (strcmp(buffer, "sqrt") == 0)
            memory = sqrt(memory);
        else if (isArithmeticOp(buffer))
        {
            b = getDigit("Zadejde cislo 2: ", "\nNezadal jste cislo, zkuste znovu\n");

            if (strcmp(buffer, "+") == 0)
                memory += b;
            else if (strcmp(buffer, "-") == 0)
                memory -= b;
            else if (strcmp(buffer, "*") == 0)
                memory *= b;
            else
            {
                if (b == 0)
                {
                    fputs("Nulou delit nelze\n", stdout);
                    continue;
                }

                memory /= b;
            }
        }
        else
            continue;
        
        printf("Vysledek: %f\n", memory);
    }

    return 0;
}