#include <iostream>
#include <string>
#include "tools.h"

#define ASCII_RESET "\e[0m" 
#define ASCII_COLOR_RED "\e[0;31m"
#define ASCII_COLOR_GREEN "\e[0;32m" 
#define ASCII_COLOR_YELLOW "\e[0;33m" 

bool get_long_long(std::string prompt, long long &n)
{
    std::string s;
    std::cout << prompt;
    std::cin >> s;
    std::cin.ignore();
    if (s == "exit" || s == "quit" || s == "q") return false;
    bool isdigit = true;
    for (char c : s) 
    {
        if (!std::isdigit(c) && c != 'e' && c != '.' && c != '-') isdigit = false;
    }
    if (isdigit && (std::isdigit(s[0]) || s[0] == '-') && std::isdigit(s[s.size() - 1]))
    {
        n = std::stoll(s);
        return true;
    }
    else
    {
        std::cout << ASCII_COLOR_RED"[*] \"" << s << "\" not a number!" ASCII_RESET << std::endl;
        return false;
    }
}

bool get_long_double_matrix(std::string prompt, long double **a, long long n)
{
    std::string s;
    std::cout << prompt;
    for (long long i = 0; i < n; i++)
    {
        for (long long j = 0; j < n; j++)
        {
            std::cin >> s;
            std::cin.ignore();
            if (s == "exit" || s == "quit" || s == "q") return false;
            bool isdigit = true;
            for (char c : s) 
            {
                if (!std::isdigit(c) && c != 'e' && c != '.' && c != '-') isdigit = false;
            }
            if (isdigit && (std::isdigit(s[0]) || s[0] == '-') && std::isdigit(s[s.size() - 1]))
            {
                a[i][j] = std::stold(s);
            }
            else
            {
                std::cout << ASCII_COLOR_RED"[*] \"" << s << "\" not a number!" ASCII_RESET << std::endl;
                return false;
            }
        }
    }
    return true;
}

void calculate()
{
    long long n, m;
    if (!get_long_long("Write N: ", n)) return;
    long double **a = new long double *[n];
    for (long long i = 0; i < n; i++)
        a[i] = new long double[n];
    if (!get_long_double_matrix("Write matrix elments: \n", a, n)) return;
    std::cout << "[*] Size: " << n << std::endl << "[*] Matrix: " << std::endl;
    for (long long i = 0; i < n; i++)
    {
        std::cout << "\t";
        for (long long j = 0; j < n; j++)
            std::cout << a[i][j] << " ";
        std::cout << std::endl;
    }
    long double result[2];
    get_shaded_matrix_values(a, n, result);
    delete[] a;
    a = nullptr;
    std::cout << ASCII_COLOR_GREEN"[*] Result: " << std::endl << "\tSum: " << result[0] << "\tProduct: " << result[1] << ASCII_RESET << std::endl;
}

void help()
{
    std::cout << ASCII_COLOR_YELLOW"\n\tcalc\tcalulate" << std::endl;
    std::cout << "\thelp\tcommands info" << std::endl;
    std::cout << "\texit\texit from program\n" ASCII_RESET << std::endl;
}

int main(int argc, char const *argv[])
{
    std::cout << ASCII_COLOR_YELLOW"\n\tWelcome to Task 3 Option 13!\n\n\tBy Skrobot Denis\n\n\tThis program find the sum and product of elements located in the shaded part matrices, see figure “a”\n" << std::endl;
    std::cout << "[*] Write \"calc\" for calculate, write \"help\" for more info\n" ASCII_RESET << std::endl;
    while (true)
    {
        std::string command;
        std::cout << ASCII_COLOR_GREEN"~$ \x1b[0m" ASCII_RESET;
        getline(std::cin, command);
        if (command == "")
            continue;
        else if (command == "calc")
            calculate();
        else if (command == "help")
            help();
        else if (command == "exit" || command == "quit" || command == "q")
            return 0;
        else
            std::cout << ASCII_COLOR_RED"[*] Command \"" << command << "\" not found! Write \"help\" for more info" ASCII_RESET << std::endl;
    }
    return 0;
}