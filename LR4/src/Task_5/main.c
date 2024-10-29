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

bool get_char_matrix(char *prompt, char **a, long long n, long long m)
{
    printf("%s", prompt);
    for (long long i = 0; i < n; i++)
    {
        for (long long j = 0; j < n; j++)
        {
            char c;
            scanf("%c", &c);
            fflush(stdin);
            if (c == 'q') 
                return false;
            else if (c == '.' || c == '*')
                a[i][j] = c;
            else if (c == '\t' || c == '\n')
            {
                j--;
                continue;
            }
            // bool isdigit = true;
            // for (int i = 0; i < strlen(s); i++)
            // {
            //     char c = s[i];
            //     if (!('0' <= c && c <= '9') && c != 'e' && c != '.' && c != '-') isdigit = false;
            // }
            // if (isdigit && ('0' <= s[0] && s[0] <= '9' || s[0] == '-') && '0' <= s[strlen(s) - 1] && s[strlen(s) - 1] <= '9')
            // {
            //     a[i][j] = atoll(s);
            // }
            else
            {
                char temp[1024];
                scanf("%s", temp);
                printf(ASCII_COLOR_RED"[*] '%c' not a correct character!\n", c);
                return false;
            }
        }
    }
    return true;
}

void calculate()
{
    long long n, m;
    if (!get_long_long("Write n: ", &n)) return;
    if (!get_long_long("Write m: ", &m)) return;
    char **a = malloc(n * sizeof(char *));
    for (long long i = 0; i < n; i++)
        a[i] = malloc(m * sizeof(char));
    if (!get_char_matrix("Write matrix elments: \n", a, n, m)) return;
    printf("[*] Size: %lldx%lld\n[*] Matrix: \n\n", n, m);
    for (long long i = 0; i < n; i++)
    {
        printf("\t");
        for (long long j = 0; j < n; j++)
            printf("%c", a[i][j]);
        printf("\n");
    }
    minesweeper(a, n, m);
    printf(ASCII_COLOR_GREEN"\n[*] Result: \n\n");
    for (long long i = 0; i < n; i++)
    {
        printf("\t");
        for (long long j = 0; j < m; j++)
            printf("%c", a[i][j]);
        printf("\n");
    }
    printf("\n" ASCII_RESET);
    for (long long i = 0; i < n; i++)
        free(a[i]);
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
    printf(ASCII_COLOR_YELLOW"\n\tWelcome to Task 5!\n\n\tBy Skrobot Denis\n\n\tThis is MINESWEEPER!\n\n");
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