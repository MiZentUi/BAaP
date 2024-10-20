#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "tools.h"

#define ASCII_RESET "\e[0m" 
#define ASCII_COLOR_RED "\e[0;31m"
#define ASCII_COLOR_GREEN "\e[0;32m" 
#define ASCII_COLOR_YELLOW "\e[0;33m" 

bool get_long_long(char *prompt, long long *n)
{
    char s[1024];
    printf("%s", prompt);
    scanf("%s", s);
    fflush(stdin);
    if (s == "exit" || s == "quit" || s == "q") return false;
    bool isdigit = true;
    for (int i = 0; i < strlen(s); i++)
    {
        char c = s[i];
        if (!('0' <= c && c <= '9') && c != 'e' && c != '.' && c != '-') isdigit = false;
    }
    if (isdigit && ('0' <= s[0] && s[0] <= '9' || s[0] == '-') && '0' <= s[strlen(s) - 1] && s[strlen(s) - 1] <= '9')
    {
        *n = atoll(s);
        return true;
    }
    else
    {
        printf(ASCII_COLOR_RED"[*] \"%s\" not a number!\n", s);
        return false;
    }
}

bool get_long_double_3d_array(char *prompt, long double ***a, long long n)
{
    char s[1024], current_string[1024];
    printf("%s", prompt);
    for (long long i = 0; i < n; i++)
    {
        for (long long j = 0; j < n; j++)
        {
            for (long long k = 0; k < n; k++)
            {
                scanf("%s", s);
                fflush(stdin);
                if (s == "exit" || s == "quit" || s == "q") return false;
                bool isdigit = true;
                for (int i = 0; i < strlen(s); i++)
                {
                    char c = s[i];
                    if (!('0' <= c && c <= '9') && c != 'e' && c != '.' && c != '-') isdigit = false;
                }
                if (isdigit && ('0' <= s[0] && s[0] <= '9' || s[0] == '-') && '0' <= s[strlen(s) - 1] && s[strlen(s) - 1] <= '9')
                {
                    a[i][j][k] = atoll(s);
                }
                else
                {
                    printf(ASCII_COLOR_RED"[*] \"%s\" not a number!\n", s);
                    return false;
                }
            }
        }
    }
    return true;
}

void calculate()
{
    long long n;
    if (!get_long_long("Write N: ", &n)) return;
    long double ***a = (long double ***) malloc(n * sizeof(long double **));
    for (long long i = 0; i < n; i++)
    {
        a[i] = (long double **) malloc(n * sizeof(long double *));
        for (long long j = 0; j < n; j++)
        {
            a[i][j] = (long double *) malloc(n * sizeof(long double));
        }
    }
    if (!get_long_double_3d_array("Write 3D array elments: \n", a, n)) return;
    printf("[*] Size: %lld\n[*] 3D array: \n\n", n);
    for (long long i = 0; i < n; i++)
    {
        for (long long j = 0; j < n; j++)
        {
            for (long long o = 0; o < n - j; o++)
                printf("     ");
            for (long long k = 0; k < n; k++)
                printf("%6Lg     ", a[i][j][k]);
            printf("\n\n");
        }
        printf("\n");
    }
    printf(ASCII_COLOR_GREEN"[*] Result: %Lg\n"ASCII_RESET, get_max_diagonal(a, n));
    for (long long i = 0; i < n; i++)
    {
        for (long long j = 0; j < n; j++)
            free(a[i][j]);
        free(a[i]);
    }
    free(a);
    a = NULL;
}

void help()
{
    printf(ASCII_COLOR_YELLOW"\n\tcalc\tcalulate\n");
    printf("\thelp\tcommands info\n");
    printf("\texit\texit from program\n\n" ASCII_RESET);
}

int main(int argc, char const *argv[])
{
    printf(ASCII_COLOR_YELLOW"\n\tWelcome to Task 3 Option 13!\n\n\tBy Skrobot Denis\n\n\tThis program determine the diagonal with the largest the sum of numbers\n\n");
    printf("[*] Write \"calc\" for calculate, write \"help\" for more info\n\n" ASCII_RESET);
    while (true)
    {
        char command[1024];
        char *buffer = command;
        size_t size = 1024;
        fflush(stdin);
        printf(ASCII_COLOR_GREEN "~$ \x1b[0m" ASCII_RESET);
        scanf("%s", command);
        if (!strcmp(command, ""))
            continue;
        else if (!strcmp(command, "calc"))
            calculate();
        else if (!strcmp(command, "help"))
            help();
        else if (!strcmp(command, "exit") || !strcmp(command, "quit") || !strcmp(command, "q"))
            return 0;
        else
            printf(ASCII_COLOR_RED"[*] Command \"%s\" not found! Write \"help\" for more info\n" ASCII_RESET, command);
    }
    return 0;
}